
var initP = 0.1000;
var initQ = 100;
var initR = 1000;


var points = [[348,92],[246,139],[302,147],[293,176],[252,176],[262,243],[188,177],[201,276],[168,261],[131,324],[83,319],[76,364],[37,374]];


var W = [[1, 0, 0, 0],[0, 1, 0, 0],[0, 0, 1, 0],[0, 0, 0, 1]];


var H = [[1,0,0,0],[0,1,0,0]];

var V = [[1,0,0,0],[0,1,0,0]];


var R = [[initR, 0, 0 ,0],[0, initR, 0, 0],[0, 0, initR, 0],[0, 0, 0, initR]];

var Q = [[initQ, 0, 0, 0],[0, initQ, 0, 0],[0, 0, initQ, 0],[0, 0, 0, initQ]];


var debugM = function(M) {
    
    debug("\n M: \n");
	
	var i,j;
	
	for(i=0;i<M.length;i++) {
        for(j=0;j<M[i].length;j++) {
            debug(M[i][j]);
		}
	}
	debug("\n");
};

var normalizeM = function(A) {
    
    var total = 0;
    
    for (var i=0; i < A.length; i++)
    {
        total = total + pow(A[i],2);
    }
    
    total = sqrt(total);
    
    if ( total < 0.000001 )
    {
        return A;
    }
    
    var B = [];
    
    for (i=0; i < A.length; i++)
    {
        B[i] = A[i]/total;
    }
    
    return B;
};

var multM = function(A,B) {
    
    var i,j,k;
    
    var sizeA1 = A.length;
	var sizeA2 = A[0].length;
    var sizeB1 = B.length;
    var sizeB2 = B[0].length;
		
    var C = [];
    
    for( i = 0; i < sizeA1; i++ )
    {
        C[i] = [];
        
        for( j = 0; j < sizeB2; j++ )
        {
            C[i][j] = 0;
             
            for( k = 0; k < sizeB1; k++ )
            {
                C[i][j] = C[i][j] + A[i][k]*B[k][j];    
            }
        }
    }
    
    return C;
};

var transposeM = function(A) {
    
    var i,j;
	
    var sizeA1 = A.length; 
    var sizeA2 = A[0].length;
    
    var C = [];
    
    for( i = 0; i < sizeA2; i++ )
    {
        C[i] = [];
    }
    
    for( j = 0; j < sizeA2; j++ )
    {
        for( i = 0; i < sizeA1; i++ )
        {
            C[j][i] = A[i][j];
        }
    }
    
    return C;
};

var addM = function(A,B) {
    
    var C = [];
    
    for( var i = 0; i < A.length; i++ )
    {
        C[i] = [];
        
        for( var j = 0; j < A[i].length; j++ )
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    
    return C;
};

var subM = function(A,B) {
    
    var C = [];
    
    for( var i = 0; i < A.length; i++ )
    {
        C[i] = [];
        
        for( var j = 0; j < A[i].length; j++ )
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    
    return C;
};

var divS = function(A,s) {
    
    var C = [];
    
    for( var i = 0; i < A.length; i++ )
    {
        C[i] = [];
        
        for( var j = 0; j < A[i].length; j++ )
        {
            C[i][j] = A[i][j]/s;
        }
    }
    
    return C;
};

var inverseM = function(A) {
    
    // create helper matrix
    var B = [];
    
    var i;
    var j;
    var k;
    
    var max;
    var row;
    var temp;
    
    for( i = 0; i < A.length; i++ )
    {
        B[i] = [];
        
        for( j = 0; j < A.length; j++ )
        {
            B[i][j] = A[i][j];
        }
        
        for( k = 0; k < A.length; k++ )
        {
            if(i === k)
            {
                B[i][ k+A.length ] = 1;
            }
            else
            {
                B[i][ k+A.length ] = 0;
            }
        }
    }
    
    for( i = 0; i < B.length; i++ )
    {
        // find maximum
        max = B[i][i];
        row = i;
        
        for( j = i; j < B.length; j++ )
        {
            if( B[j][i] > max )
            {
                max = B[j][i];
                row = j;
            }
        }
        
        // reorder the rows
        for( j = 0; j < B.length*2; j++ )
        {
            if( row === i )
			{
				B[i][j] = B[i][j] / max;
			}
			else
			{
                temp = B[i][j];
                B[i][j] = B[row][j] / max;
                B[row][j] = temp;
			}
        }
		
        for( j = i+1; j < B.length; j++ )
        {
            max = B[j][i];
            
            for( k = i; k < B.length*2; k++ )
            {
                B[j][k] = B[j][k] - B[i][k]*max;
            }
        }
	}	
	
	for( i = B.length-1; i >= 0; i-- )
    {		
        for( j = i-1; j >= 0; j-- )
        {
            max = B[j][i];
            
            for( k = i; k < B.length*2; k++ )
            {
                B[j][k] = B[j][k] - B[i][k]*max;
            }
        }
    }
	
    var D = [];
    
    for( i = 0; i < B.length; i++ )
    {
        D[i] = [];
        
        for( j = 0; j < B.length; j++ )
        {
            D[i][j] = B[i][j+B.length];
        }
    }
    
    return D;
};

var predictX = function(X)
{
    var F = [[1,0,1,0],[0,1,0,1],[0,0,1,0],[0,0,0,1]];
    
    var predictedX = multM(F,X);
    
    return predictedX;
};

var setup = function()
{
    background(212, 212, 212);
};

var draw = function() {

    background(255, 255, 255);
    
    var Xk = [[points[0][0]],[points[0][1]],[0],[0]];
    var Pk = [[initP, 0, 0, 0],[0, initP, 0, 0],[0, 0, initP, 0],[0, 0, 0, initP]];
    
    var i;
    var last_estimate = [Xk[0][0],Xk[1][0]];
    
    for(i=1;i<points.length;i++)
    {
        // ESTIMATE
        var measurement = [[points[i][0]],[points[i][1]]];
    
        var A = [[1,0,1,0],[0,1,0,1],[0,0,1,0],[0,0,0,1]];
        
        // TIME UPDATE
        
        // 1) PROJECT Xk
        var projectedX = predictX(Xk);
        
        // 2) PROJECT Pk
        var projectedP = addM( multM(multM(A,Pk),transposeM(A)), multM(multM(W,Q),transposeM(W)) );
        
        // MEASUREMENT UPDATE
        
        // 1) KALMAN GAIN
        var Kk = multM( multM(projectedP,transposeM(H)) , inverseM( addM( multM(multM(H,projectedP),H) , multM(multM(V,R),transposeM(V)) ) ) );
        
        // 2) UPDATE ESTIMATE
        Xk = addM( projectedX , multM( Kk , subM( measurement , multM(H,projectedX) ) ) );
        
        // 3) UPDATE ERROR COVARIENCE
        Pk = multM( subM( [[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]] , multM(Kk , H)), projectedP);
        
        // print measurements
        fill(0, 34, 255);
        line(points[i-1][0], points[i-1][1], points[i][0], points[i][1]);
        ellipse(points[i-1][0], points[i-1][1], 10, 10);
        ellipse(points[i][0], points[i][1], 10, 10);
        
        // print estimates
        fill(255, 34, 255);
        line(last_estimate[0], last_estimate[1], Xk[0][0], Xk[1][0]);
        ellipse(last_estimate[0], last_estimate[1], 10, 10);
        ellipse(Xk[0][0], Xk[1][0], 10, 10);
        
        last_estimate = [Xk[0][0],Xk[1][0]];
    }
};

