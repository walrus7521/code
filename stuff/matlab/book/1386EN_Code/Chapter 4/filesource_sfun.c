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

#define S_FUNCTION_NAME filesource_sfun
#define S_FUNCTION_LEVEL 2

#include <stdio.h>
#include "simstruc.h" /* mandatory */
#include "matrix.h"   /* helper functions */

/* maximum file path length */
#define FILEPATH_LEN 200
/* line large enough for 64 bit doubles + \0 */
#define FILELINE_LEN 1080

/* 
 * Called before the simulation or
 * when the model is updated
 */
static void mdlInitializeSizes(SimStruct *S)
{
    /* set number of S-function parameters */
    ssSetNumSFcnParams(S, 2); 
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
        return; /* Parameter mismatch will be reported by Simulink */
    
    /* set parameters as non-tunable during simulation */
    ssSetSFcnParamTunable(S, 0, SS_PRM_NOT_TUNABLE);
    ssSetSFcnParamTunable(S, 1, SS_PRM_NOT_TUNABLE);

    ssSetNumContStates(S,0); /* no continuous states (integrators/derivators) */
    ssSetNumDiscStates(S,0); /* no discrete states (unit delay/memory) */
    
    if (!ssSetNumInputPorts(S,0)) /* set inports number to 0 */
    return;

    if (!ssSetNumOutputPorts(S, 1)) /* set number of outports */
    return;
    ssSetOutputPortWidth(S, 0, 1); /* set outport width (scalar) */
    ssSetOutputPortDataType(S, 0, SS_DOUBLE); /* set outport type */

    ssSetNumSampleTimes(S, 1); /* one block-based sample time */

    ssSetNumDWork(S, 1);                  /* needed vectors: 1 */
    ssSetDWorkWidth(S, 0, 1);             /* the vector 0 has only 1 element */
    ssSetDWorkDataType(S, 0, SS_DOUBLE);  /* and will hold a real signal */
    
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
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    /* apply no offset */
    ssSetOffsetTime(S, 0, 0.0);

    #ifndef NDEBUG
    printf("mdlInitializeSampleTimes called\n");
    #endif
}

/*
 * Called right before the first simulation cycle
 */
#define MDL_START
#ifdef MDL_START
static void mdlStart(SimStruct *S)
{    
    real_T *yPrev = NULL; /* pointer to DWork element */
    real_T yInit = 0.0;   /* tmp variable to read parameter */
    
    /* get the previous output from DWork */
    yPrev = (real_T*) ssGetDWork(S,0);
    
    /* get the default output from 2nd parameter */
    yInit = mxGetScalar(ssGetSFcnParam(S, 1));
    
    /* set the previous output to the default output */
    yPrev[0] = yInit;
    
    #ifndef NDEBUG
    printf("mdlStart: got initial output %f\n", yInit);
    #endif
}
#endif /* MDL_START */

/*
 * Called in the simulation loop
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    FILE *fd = NULL;
    char_T path[FILEPATH_LEN];
    char_T line[FILELINE_LEN];
    char_T *lineEnd;
    real_T *y = NULL;
    real_T *yPrev = NULL;
    real_T yOut;
    UNUSED_ARG(tid);
    
    /* get the output pointer */
    y = ssGetOutputPortRealSignal(S,0);
    
    /* get the previous output pointer from DWork */
    yPrev = (real_T*) ssGetDWork(S,0);
    
    /* get the filename for reading */
    memset(path, 0, FILEPATH_LEN);
    mxGetString(ssGetSFcnParam(S,0), path, FILEPATH_LEN);
	
	/* open file for reading */
    fd = fopen(path, "r");
    if(fd == NULL)
    {
        printf("Error: source file %s not readable\n", path);
        y[0] = yPrev[0];
        return;
    }
    
    /* copy the last line of the file into the buffer */
    memset(line, 0, FILELINE_LEN);
    if (fgets(line, FILELINE_LEN, fd) == NULL) /* error or empty file */
    {
        printf("Error: source file %s empty\n", path);
        y[0] = yPrev[0];
        fclose(fd);
        return;
    }

    /* convert from string to double */
    lineEnd = NULL;
    yOut = strtod(line, &lineEnd);
    if(lineEnd == line)
    {
        printf("Error: string to double conversion failed");
        y[0] = yPrev[0];
        fclose(fd);
        return;
    }
    
    /* if we reach here everything went good */
    
    #ifndef NDEBUG
    printf("%s value: %f\n",path, yOut);
    #endif

    /* set the output */
    y[0] = yOut;

    /* close the file */
    fclose(fd);
}


/*
 * Called after mdlOutputs
 */
#define MDL_UPDATE
#ifdef MDL_UPDATE
static void mdlUpdate(SimStruct *S, int_T tid)
{
    real_T *y = NULL;
    real_T *yPrev = NULL;
    UNUSED_ARG(tid);
    
    /* get the output pointer */
    y = ssGetOutputPortRealSignal(S,0);
    
    /* get the previous output pointer from DWork */
    yPrev = (real_T*) ssGetDWork(S,0);
    
    /* update the previous output */
    yPrev[0] = y[0];
    
    #ifndef NDEBUG
    printf("mdlUpdate: saved output %f\n", yPrev[0]);
    #endif
}
#endif /* MDL_UPDATE */

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
