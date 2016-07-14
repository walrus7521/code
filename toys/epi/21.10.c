/*
 * Implement Mileage Run
 *  Airlines often give customers who fly frequently with them a "status".  This status
 *  allows them early boarding, more baggage, upgrades to execute class, etc.  Typically,
 *  status is a function of miles flown in the past twelve months.  People who travel
 *  frequently by air sometimes want to take a round trip flight simply to maintain their
 *  status.  The destination is immaterial - the goal is to minimize the cost-per-mile
 *  (cpm), ie, the ratio of dollars spent to miles flown.
 *
 *  Design a system that will help its users find mileage runs.
 *
 */


/*
 *  1. Front end user web interface.
 *      a. Gives user the current status, miles available.
 *      b. Options for using the miles.
 *      c. Charts on award types and class of services.
 *      d. Charts for accumulating miles via destinations.
 *      e. Charts for accumulating miles via class-of-service.
 *      f. Information on how to accumulate miles from other airlines.
 *  2. Backend database and web server.
 *      a. tracks users mileage flown in last 12 months.
 *      b. provides databases of destinations and mileage, to support
 *      all above front-end requirements.
 *      c. Mining of the users behavior to better tailor the program to
 *      customers' actual needs.
 */

/* 
 *  Calculate the approximate server workload by estimating the number of 
 *  rewards card holders, and the frequency with which they fly.
 *
 *  Based on the workload, and amount of data generated, design a storage and 
 *  database system for storage and retrieval that scales to this load.
 */
