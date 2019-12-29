#!/usr/local/bin/octave -qf

samples = struct ("patient", {"Bob", "Kevin", "Bob" , "Andrew"},
                   "age",     { 45  ,  52    ,  45   ,  23     },
                   "protein", {"H2B", "CDK2" , "CDK2", "Tip60" },
                   "tube"   , { 3   ,  5     ,  2    ,  18     }
                   );

## [samples(:).patient]
## [samples(:).age]
## [samples(:).protein]
## [samples(:).tube]

reshape ([samples(:).patient], size (samples))
reshape ([samples(:).age], size (samples))
reshape ([samples(:).protein], size (samples))
reshape ([samples(:).tube], size (samples))


