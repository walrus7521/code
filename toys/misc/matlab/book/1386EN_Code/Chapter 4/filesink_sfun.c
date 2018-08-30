/**************************************************************************
Copyright (c) 2013, Luca Zamboni <zamboluca@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************************/

#define S_FUNCTION_NAME filesink_sfun
#define S_FUNCTION_LEVEL 2

#include <stdio.h>
#include "simstruc.h"
#include "matrix.h"

/* maximum file path length */
#define FILEPATH_LEN 200

/* 
 * Called before the simulation or
 * when the model is updated
 */
static void mdlInitializeSizes(SimStruct *S)
{
    /* set number of S-function parameters */
    ssSetNumSFcnParams(S, 1); 
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
        return; /* Parameter mismatch will be reported by Simulink */
    
    /* set parameters as non-tunable during simulation */
    ssSetSFcnParamTunable(S, 0, SS_PRM_NOT_TUNABLE);

    ssSetNumContStates(S, 0); /* no continuous states (integrators/derivators) */
    ssSetNumDiscStates(S, 0); /* no discrete states (unit delay/memory) */
    
    if (!ssSetNumInputPorts(S, 1)) /* set input ports number to 1 */
    return;
    ssSetInputPortWidth(S, 0, 1); /* set inport width (scalar) */
    ssSetInputPortDataType(S, 0, SS_DOUBLE); /* set inport type */
    ssSetInputPortRequiredContiguous(S, 0, 1); /* needed by ssGetInputPortRealSignal() */
    
    /* mdlOutputs needs to read the input */
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 0)) /* set number of outports */
    return;

    ssSetNumSampleTimes(S, 1); /* one block-based sample time */
    
    /* We don't need a work vector. */
    
    #ifndef NDEBUG
    printf("mdlInitializeSizes called\n");
    #endif
}

/*
 * Called before the simulation or
 * when the model is updated
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    /* set the sample time to use */
    /* source block (with no input) may have CONTINUOUS_SAMPLE_TIME or VARIABLE_SAMPLE_TIME */
    /* other blocks can inherit from the driving ones: INHERITED_SAMPLE_TIME */
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    /* apply no offset */
    ssSetOffsetTime(S, 0, 0.0);
    
    #ifndef NDEBUG
    printf("mdlInitializeSampleTimes called\n");
    #endif
}

/*
 * Called in the simulation loop
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    FILE *fd = NULL;
    char_T path[FILEPATH_LEN];
    const real_T *u = NULL;
    UNUSED_ARG(tid);

    /* open the file for writing */
    memset(path, 0, FILEPATH_LEN);
    mxGetString(ssGetSFcnParam(S, 0), path, FILEPATH_LEN);
    fd = fopen(path, "w");
    if(fd == NULL)
    {
        printf("Error: sink file %s not writable\n", path);
        return;
    }
    else
    {
        /* disable file buffering */
        setbuf(fd, NULL);
    }

    /* set the input port pointer */
    u = ssGetInputPortRealSignal(S, 0);
    #ifndef NDEBUG
    printf("%s value: %f\n", path, u[0]);
    #endif

    /* write input to file */
    fprintf(fd, "%f", u[0]);
    
    /* close the file */
    fclose(fd);
}

/*
 * Called when the simulation ends
 */
static void mdlTerminate(SimStruct *S)
{
    UNUSED_ARG(S);
    
    #ifndef NDEBUG
    printf("mdlTerminate successfully called\n");
    #endif
}

/*=============================*
 * Required S-function trailer *
 *=============================*/
#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file?*/
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif
