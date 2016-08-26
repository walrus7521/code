#!/usr/bin/python

from numpy import *
from numpy import linalg

def VECTOR3():
    arr = [0, 0, 0]
    arr = array(arr)
    return arr

def MATRIX3X3():
    M = [[0, 0, 0],
         [0, 0, 0],
         [0, 0, 0]]
    M  = matrix(M)
    return M

class EULER_ANGLES(object):
    phi   = 0.0 # float
    theta = 0.0 # float
    psi   = 0.0 # float

class EULER_RATES(object):
    phi_dot   = 0.0 # floats
    theta_dot = 0.0
    psi_dot   = 0.0


class ADAHRS_COEFF_STRUCT(object):
    #// gain of the proportional aspect of the complimentary filter
    #// these are corelated to the "real world" using "delta_time"
    #// these gains are calculated outside the scope of the ADAHRS
    #// in order to relieve the responsibility of ensuring a safe division.
    #// Zeta is the damping factor and it unitless
    #// Tau is the time-constant, in seconds
    #// Kp = 2 * Zeta / Tau
    gain_down_proportional = 0.0
    gain_North_proportional = 0.0

    #// gain of the integral aspect of the complimentary filter
    #// these are corelated to the "real world" using "delta_time"
    #// these gains are calculated outside the scope of the ADAHRS
    #// in order to relieve the responsibility of ensuring a safe division.
    #// Tau is the time-constant, in seconds
    #// Ki = (1 / Tau)^2
    gain_down_integral = 0.0
    gain_North_integral = 0.0

    #// Maximum frame-by-frame deviation allowed in the magnetometer vector during initialization
    fast_mag_min_dot_product = 0.0
    #// Maximum long term deviation allowed in the magnetometer vector during initialization
    #// relative to a baseline average.
    slow_mag_min_dot_product = 0.0

    #// Maximum deviation allowed in the accelerometer vector, relative to the ideal straight down (0, 0, 1)
    #// vector, during initialization
    accel_min_dot_product = 0.0
    #// Maximum magnitude of the accelerometer vector allowed during initialization.
    initialization_accel_magnitude_max = 0.0
    #// Minimum magntidue of the accelerometer vector allowed during initialization.
    initialization_accel_magnitude_min = 0.0

    #// Additional low pass filter applied to accelerometer data when checking for a stationary aircraft
    accel_init_low_pass_filter_alpha = 0.0
    #// Additional low pass filter applied to magnetometer data when checking for a stationary aircraft
    mag_init_low_pass_filter_alpha = 0.0

    #// these are discrete iteration counters correlated to calls to ADAHRS_Run()
    #// The first frame when we start collecting data to see whether or not the
    #// aircraft is stationary while the ADAHRS is initializing. This must happen
    #// before we start accumulating and averaging sensor data
    initialization_stationary_check_start = 0
    #// how long to wait before starting the gyro averaging
    initialization_start_rates = 0
    #// how long to wait before starting the magnetometer and accelerometer averaging
    initialization_start_mags_accels = 0
    #// when the sensor averaging period should end
    initialization_end_sensor_init = 0
    #// when the system should be considered operational following preliminary averaging (allows time for
    #// estimates from averaging to "settle" to their true value in case the aircraft was not stationary, etc.
    #// This value MUST be strictly greater than the other 'initialization_...' iteration counters.
    initialization_system_is_op = 0


class ESTIMATES(object):
    # aircraft's Euler attitude; radians
    euler_angles = EULER_ANGLES()
    # aircraft's Euler rates; radians per second
    euler_angular_rates = EULER_RATES()
    # body rates; radians per second
    body_angular_rates = VECTOR3()

class ADAHRS_STATE_STRUCT(object):
    iteration = None
    # rotation matrix which can be used to rotate an arbitrary vector from body axes to Earth axes
    R_to_Earth_from_body = MATRIX3X3()
    # rotation matrix which can be used to rotate an arbitrary vector from Earth axes to body axes
    R_to_body_from_Earth = MATRIX3X3()
    # holds the error between the current down/North estimates and the most recent down/North measurements
    # currently, the errors are calculated using the cross product of the estimate with the measurement
    # which means that the units of these vectors are radians and the magnitudes are proportional
    # to the sin() of the angle between the estimate and measured vectors
    down_error = VECTOR3()
    North_error = VECTOR3()
    # holds the total integral correction to be applied during the next update phase
    # units are radians per second
    integral_correction = VECTOR3()
    # holds the total proportional correction to be applied during the next update phase
    # units are radians per second
    proportional_correction = VECTOR3()
    estimates = ESTIMATES()

class ADAHRS_INPUT_STRUCT(object):
    # radians per second - +P through nose, +Q through right door, +R through floor
    measured_angular_rates = VECTOR3()
    # Gs - +X through nose, +Y through right door, +Z through floor
    measured_G_forces = VECTOR3()
    # unitless - +X through nose, +Y through right door, +Z through floor
    measured_magnetic_field = VECTOR3()
    measured_delta_time = 0.0

class ADAHRS(object):
    inputs = ADAHRS_INPUT_STRUCT() # holds the inputs for this instance
    state  = ADAHRS_STATE_STRUCT() # holds the state for this instance
    coeff_ptr = ADAHRS_COEFF_STRUCT()

def LinAlg_Scalar_Vect3_Multiply(scalar, B):
    return (scalar*B)

def LinAlg_Vect3_Dot_Product(A, B):
    Bt = transpose(B)
    return (A*Bt)

def LinAlg_Vect3_Cross_Product(A, B):
    return cross(A, B)

def LinAlg_Vect3_Add(A, B):
    return (A+B)

def LinAlg_Vect3_Sub(A, B):
    return (A-B)

def LinAlg_Vect3_Normalize(A):
    Anorm = linalg.norm(A)
    if (Anorm == 0):
        return VECTOR3()
    Bnorm = A/Anorm
    return Bnorm

def LinAlg_Mtx3x3_Transpose(A):
    At = transpose(A)
    return (At)

def LinAlg_Mtx3x3_Mtx3x3_Multiply(A, B):
    Bt = matrix.transpose(B)
    return (A*Bt)
 
def LinAlg_Mtx3x3_Vect3_Multiply(M, V):
    result = VECTOR3()
    V = matrix(transpose(V))
    result[0] = LinAlg_Vect3_Dot_Product(M[0], V)
    result[1] = LinAlg_Vect3_Dot_Product(M[1], V)
    result[2] = LinAlg_Vect3_Dot_Product(M[2], V)
    return result

def ADAHRS_Initialize():
    adahrs = ADAHRS()
    return adahrs

def ADAHRS_Update_DCM_Transforms(adahrs):
    #measurement conversion stuff
    #rates_no_bias_w_correction_dt_body = VECTOR3() # (bias-correct w/ proportional-correct) * dt
    # scale omega by DT to form omega_dt
    rates_no_bias_w_correction_dt_body = LinAlg_Scalar_Vect3_Multiply(adahrs.inputs.measured_delta_time, 
            adahrs.state.estimates.body_angular_rates);
    print rates_no_bias_w_correction_dt_body
    # build the update matrix
    ADAHRS_Update_Rotation_Matrix(adahrs.state.R_to_body_from_Earth, 
            rates_no_bias_w_correction_dt_body);
    #// generate and store the inverse-transform
    adahrs.state.R_to_Earth_from_body = LinAlg_Mtx3x3_Transpose(adahrs.state.R_to_body_from_Earth)
    return

def ADAHRS_Update_Rotation_Matrix(R, omega_dt):
    # input: MATRIX3X3 * R_ptr, VECTOR3 const * omega_dt_ptr)
    R_dot = [[ 1.0,          omega_dt[2],  -omega_dt[1]],
             [-omega_dt[2],  1.0,           omega_dt[0]],
             [ omega_dt[1], -omega_dt[0],   1.0]]
    R_dot = matrix(R_dot)

    #// update R using the update matrix to generate R-new
    R_new = LinAlg_Mtx3x3_Mtx3x3_Multiply(R_dot, R)

    print R_new
    #// the magnitude of the orthogonality error is the cross-product
    ortho_error = LinAlg_Vect3_Dot_Product(R_new[0], R_new[1])

    #// subtract half of the error from row 1 to make it orthogonal with row 2
    ortho_correction = LinAlg_Scalar_Vect3_Multiply(0.5 * ortho_error, R_new[1])
    row1_new = LinAlg_Vect3_Sub(R_new[0], ortho_correction)
    #// normalize row 1
    R[0] = LinAlg_Vect3_Normalize(row1_new)

    #// subtract half of the error from row 2 to make it orthogonal with row 1
    ortho_correction = LinAlg_Scalar_Vect3_Multiply(0.5 * ortho_error, R_new[0])
    row2_new = LinAlg_Vect3_Sub(R_new[1], ortho_correction)
    #// normalize row 2
    R[1] = LinAlg_Vect3_Normalize(row2_new)

    #// row 3 is the cross product of row 1 and row 2, both of which are already ortho-normal
    #// therefore the result is also ortho-normal
    R[2] = LinAlg_Vect3_Cross_Product(R[1], R[2])
    return

def ADAHRS_Euler_Estimates(adahrs):
    #// New computed euler angles
    #EULER_ANGLES new_euler_angles = {0};
    #// update the Euler angles
    #LinAlg_Mt3x3_Get_Euler_Angles(&adahrs->state.R_to_Earth_from_body, &new_euler_angles);
    #if (ADAHRS_Is_Operational(adahrs))
    #{
    #    // Compare the new and old euler angles. The euler angles should not change by more
    #    // than 250 degrees per second; this is the maximum rate the gyros can measure.
    #    F32 max_angle_diff_per_frame = adahrs->inputs.measured_delta_time * MAXIMUM_GYRO_RATE;
    #     // Compute the deltas between this frame's euler angles and last frame's euler angles.
    #     // Deltas are normalized to [-pi, pi); this accounts for the wrap-around that occurs
    #    // when traveling south.
    #    EULER_ANGLES deltas = {0};
    #    deltas.phi   = PiRads(fabsf(new_euler_angles.phi   - adahrs->state.estimates.euler_angles.phi));
    #    deltas.theta = PiRads(fabsf(new_euler_angles.theta - adahrs->state.estimates.euler_angles.theta));
    #    deltas.psi   = PiRads(fabsf(new_euler_angles.psi   - adahrs->state.estimates.euler_angles.psi));
    #    // Make sure each angle is within the specified limit.
    #    if (deltas.phi   > max_angle_diff_per_frame ||
    #        deltas.theta > max_angle_diff_per_frame ||
    #        deltas.psi   > max_angle_diff_per_frame)
    #    {
    #        Fault_Mgmt_Set_Fault(FAULT_ADAHRS_EULER_ANGLE_TRANSIENT);
    #    }
    #    // else do nothing
    #}
    #// else the ADAHRS is not operational yet, so the first euler angle estimate has not been set. do nothing
    #adahrs->state.estimates.euler_angles = new_euler_angles;
    #{ // update the Euler rates
    #    MATRIX3X3 R_to_euler_rates_from_body_rates = {0};
    #    VECTOR3 euler_rates = {0};
    #    F32 const cos_t = cosf(adahrs->state.estimates.euler_angles.theta);
    #    F32 const sin_t = sinf(adahrs->state.estimates.euler_angles.theta);
    #    F32 const cos_p = cosf(adahrs->state.estimates.euler_angles.phi);
    #    F32 const sin_p = sinf(adahrs->state.estimates.euler_angles.phi);
    #    F32 sec_t = 0.0f;
    #    F32 tan_t = 0.0f;
    #    // Protection against divide-by-zero and degenerate rotation matrices.
    #    if (COSINE_EPSILON < cos_t)
    #    {
    #        sec_t = 1.0f / cos_t; // sec(theta)
    #        tan_t = sin_t*sec_t; // tan(theta) = sin(theta) / cos(theta) = sin(theta) * sec(theta)
    #        // build the matrix
    #        R_to_euler_rates_from_body_rates.row1.X = 1;
    #        R_to_euler_rates_from_body_rates.row1.Y = sin_p*tan_t; // sin(phi)*tan(theta)
    #        R_to_euler_rates_from_body_rates.row1.Z = cos_p*tan_t; // cos(phi)*tan(theta)
    #        R_to_euler_rates_from_body_rates.row2.X =  0;
    #        R_to_euler_rates_from_body_rates.row2.Y =  cos_p; //  cos(phi)
    #        R_to_euler_rates_from_body_rates.row2.Z = -sin_p; // -sin(phi)
    #        R_to_euler_rates_from_body_rates.row3.X = 0;
    #        R_to_euler_rates_from_body_rates.row3.Y = sin_p*sec_t; // sin(phi)*sec(theta)
    #        R_to_euler_rates_from_body_rates.row3.Z = cos_p*sec_t; // cos(phi)*sec(theta)
    #        // apply the matrix to the body rates
    #        LinAlg_Mtx3x3_Vect3_Multiply(&euler_rates,
    #                                     &R_to_euler_rates_from_body_rates,
    #                                     &adahrs->state.estimates.body_angular_rates);
    #        // store the rates
    #        adahrs->state.estimates.euler_angular_rates.phi_dot =   euler_rates.X;
    #        adahrs->state.estimates.euler_angular_rates.theta_dot = euler_rates.Y;
    #        adahrs->state.estimates.euler_angular_rates.psi_dot =   euler_rates.Z;
    #    }
    #    // else cos_t is too close to zero to get accurate numbers at this point. do nothing.
    #    // In this case, the euler angular rates will not be updated. This is okay because
    #    // the euler rates are only used in the inner loop (so it will only affect the ADAHRS),
    #    // and the aircraft cannot stay at +- 90 degrees pitch for long enough to cause problems
    #    // in the inner loop.
    #} // update the Euler rates
    pass
    return

def ADAHRS_Update_Down_Error_Estimate(adahrs):
    #VECTOR3 body_velocity = {0}; // Estimate of the body's velocity
    #VECTOR3 body_accelerations_centripetal = {0}; // Estimate of the body's centripetal acceleration
    #VECTOR3 body_accelerations_delta_airspeed = {0}; // Estimate of the body's acceleration due to changes in airspeed
    #VECTOR3 body_accelerations_total = {0}; // Estimate of the body's total acceleration
    #VECTOR3 down_correction = {0}; // will hold an estimate of the body's total acceleration in "down" axes
    #VECTOR3 down_measured = {0}; // will hold the estimated "down" vector
    #// calculate the acceleration based on changes in airspeed
    #if(adahrs->state.measured_airspeed_first_pass_complete && adahrs->inputs.measured_delta_time)
    #{
    #    // first-pass completed and delta_time != 0
    #    // acceleration = delta_airspeed / delta_time
    #    body_accelerations_delta_airspeed.X =
    #        (adahrs->inputs.measured_airspeed - adahrs->state.measured_airspeed_last) /
    #        adahrs->inputs.measured_delta_time;
    #}
    #else
    #{
    #    // first-pass not yet completed or delta_time == 0
    #    // not enough information to calculate acceleration
    #    // do nothing - vector already initialized to 0
    #}
    #// form a velocity vector based on airspeed
    #body_velocity.X = adahrs->inputs.measured_airspeed;
    #body_velocity.Y = 0;
    #body_velocity.Z = 0;
    #// centripetal acceleration is the cross-product of omega with velocity
    #LinAlg_Vect3_Cross_Product(
    #    &body_accelerations_centripetal,
    #    &adahrs->state.estimates.body_angular_rates,
    #    &body_velocity);
    #// calculate the total body acceleration
    #LinAlg_Vect3_Add(
    #    &body_accelerations_total,
    #    &body_accelerations_centripetal,
    #    &body_accelerations_delta_airspeed);
    #// convert the body accelerations, in m/s^2, to a DCM "down" vector
    #// the "correction" term is the estimate of the component of the accelerometer reading
    #// which is due to changes in airspeed and due to turning
    #CONVERT_TO_DCM_FROM_MPSPS(down_correction, body_accelerations_total);
    #// subtract the estimated contribution due to changes in airspeed and due to turning from the measurement
    #LinAlg_Vect3_Sub(
    #    &down_measured,
    #    &adahrs->inputs.measured_G_forces,
    #    &down_correction);
    #// the cross product of the current DCM estimate of "down" with the measured down vector (comprised of
    #// the accelerometer measurement minus the correction term) yields a vector which is proportional to
    #// the error in the DCM estimate and the corrected accelerometer reading and is used later to correct
    #// the DCM as well as the gyro zero-rate bias estimates.
    #LinAlg_Vect3_Cross_Product(
    #    &adahrs->state.down_error,
    #    &adahrs->state.R_to_Earth_from_body.row3,
    #    &down_measured);
    pass
    return

def ADAHRS_Update_North_Error_Estimate(adahrs):
    mag_meas_Earth_raw  = VECTOR3()
    mag_error_Earth     = VECTOR3()
    #// rotate the measured magnetic vector from body axes into Earth axes
    #// if we assume that our measurement is (on average) perfect and our Euler attitude estimate is imperfect,
    #// then this rotation will yield a vector which should exist purely in the North-down plane - any component
    #// pointing East at this point is due to error in our Euler angle estimates and can be used
    #// to correct the estimates of both the Euler angles as well as the zero-rate bias of the gyros
    mag_meas_Earth_raw = LinAlg_Mtx3x3_Vect3_Multiply(adahrs.state.R_to_Earth_from_body, adahrs.inputs.measured_magnetic_field)
    #// because the Earth's magnetic field generally has some non-zero dip-angle, we throw away the Z-component
    #// of the Earth-based magnetic field vector.  This yields a vector purely in the North-East plane which
    #// can then be normalized.  Again, at this point, any component pointing East is due to error in the
    #// Euler angle estimates.
    #// throw away the "down" component
    mag_meas_Earth_raw[0] = 0
    #// normalize the vector
    mag_meas_Earth_norm = LinAlg_Vect3_Normalize(mag_meas_Earth_raw)
    #// the error is the cross product between ideal magnetic north [1, 0, 0] and the normalized north-east magnetic
    #// vector [X, Y, 0]
    #// therefore, the result is just [0, 0, Y] (IE doing the full cross-product is unnecessary)
    mag_error_Earth[0] = 0;
    mag_error_Earth[1] = 0;
    mag_error_Earth[2] = mag_meas_Earth_norm[1] # this is now an estimate of yaw error
    #// the existing error estimate is in the Earth axes - rotate into body axes
    adahrs.state.North_error = LinAlg_Mtx3x3_Vect3_Multiply(adahrs.state.R_to_body_from_Earth, mag_error_Earth)
    return

def ADAHRS_Get_Estimated_Body_Zero_Rate_Bias(adahrs):
    return LinAlg_Vect3_Add(adahrs.state.proportional_correction, adahrs.state.integral_correction)

def ADAHRS_Update_Zero_Rate_Bias_Estimate(adahrs):
    #// calculate the down proportional term
    proportional_term_down = LinAlg_Scalar_Vect3_Multiply(adahrs.coeff_ptr.gain_down_proportional, adahrs.state.down_error)
    #// calculate the North proportional term
    proportional_term_North = LinAlg_Scalar_Vect3_Multiply(adahrs.coeff_ptr.gain_North_proportional, adahrs.state.North_error)
    #// calculate the total proportional correction (applied during the next DCM update)
    adahrs.state.proportional_correction = LinAlg_Vect3_Add(proportional_term_down, proportional_term_North)
    #// calculate down integral correction term
    integral_term_down_dt = LinAlg_Scalar_Vect3_Multiply(adahrs.coeff_ptr.gain_down_integral * adahrs.inputs.measured_delta_time, adahrs.state.down_error)
    #// calculate the North integral correction term
    integral_term_North_dt =LinAlg_Scalar_Vect3_Multiply(adahrs.coeff_ptr.gain_North_integral * adahrs.inputs.measured_delta_time, adahrs.state.North_error)
    #// calculate the total integral correction term
    integral_term_total_dt = LinAlg_Vect3_Add(integral_term_down_dt, integral_term_North_dt)
    #// Do the integration
    adahrs.state.integral_correction = LinAlg_Vect3_Add(integral_term_total_dt, adahrs.state.integral_correction)
    return

def ADAHRS_Get_Estimated_Body_Zero_Rate_Bias(adahrs):
    estimated_body_zero_rate_bias = LinAlg_Vect3_Add(adahrs.state.proportional_correction, adahrs.state.integral_correction)
    return estimated_body_zero_rate_bias

def ADAHRS_Update_All(adahrs):
    zero_rate_bias = VECTOR3()
    zero_rate_bias = ADAHRS_Get_Estimated_Body_Zero_Rate_Bias(adahrs)
    print zero_rate_bias
    # Apply integral and proportional correction to the measured angular rates
    adahrs.state.estimates.body_angular_rates = LinAlg_Vect3_Sub(adahrs.inputs.measured_angular_rates, zero_rate_bias)
    print adahrs.state.estimates.body_angular_rates
    #// update the DCMs - this is the "prediction" phase
    #// the "correction" term, calculated below, is incorporated here for convenience
    ADAHRS_Update_DCM_Transforms(adahrs)
    #// update the Euler angles and Euler angular rates based on the prediction DCMs
    ADAHRS_Euler_Estimates(adahrs)
    #// update the down error estimate
    ADAHRS_Update_Down_Error_Estimate(adahrs)
    #// update the North error estimate
    ADAHRS_Update_North_Error_Estimate(adahrs)
    #// run the complementary filters to generate the "correction" term
    ADAHRS_Update_Zero_Rate_Bias_Estimate(adahrs)
    return

def ADAHRS_Run(adahrs):
    ADAHRS_Update_All(adahrs)
    # increment the iteration counter
    ++adahrs.state.iteration
    return


def main():
    adahrs = ADAHRS_Initialize()
    # set all initial conditions
    ADAHRS_Update_All(adahrs)
    exit()


if __name__ == '__main__':
    main()

