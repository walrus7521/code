%% S-function entry point
function filesource_msfun(block)
setup(block);

%% First required callback: setup
function setup(block)
block.NumDialogPrms  = 2; % Number of parameters
block.NumInputPorts  = 0; % Number of inports
block.NumOutputPorts = 1; % Number of outports

% Set the default properties to all ports
block.SetPreCompPortInfoToDefaults;

% Set the sample time and the offset time
% we won't inherit the sample time here
block.SampleTimes = [0 0];

% Specify the block simStateCompliance
% we want the block to run at each time step
block.SimStateCompliance = 'DefaultSimState';

% we'll be using a DWork vector, so we need to register the
% optional callbacks: PortPropogationSetup & Start
block.RegBlockMethod('PostPropagationSetup', @PostPropagationSetup);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);
block.RegBlockMethod('Update', @Update);

%% first optional callback: PostPropagationSetup
function PostPropagationSetup(block)
% define how many DWork vectors we need
block.NumDworks = 1;
block.Dwork(1).Name = 'lastValue'; % required!
block.Dwork(1).Dimensions = 1;
block.Dwork(1).DatatypeID = 0; % double
block.Dwork(1).Complexity = 'Real';
block.Dwork(1).Usage = 'DWork';

%% second optional callback: Start
function Start(block)
block.Dwork(1).Data = block.DialogPrm(2).Data; % holds initial output

%% third optional callback: Outputs
function Outputs(block)
% open file as readonly
fid = fopen(block.DialogPrm(1).Data, 'r');
% read one line
tline = fgetl(fid);
if (tline == -1) %  fail
    % output last value
    block.OutputPort(1).Data = block.Dwork(1).Data;
    return
end

% convert to double
output = str2double(tline);
% check that the output is a valid number
if (isnan(output)) % fail
    % output last value
    block.OutputPort(1).Data = block.Dwork(1).Data;
    return
end
%output the read value
block.OutputPort(1).Data = output;
fclose(fid);

%% forth optional callback: Update
function Update(block)
block.Dwork(1).Data = block.OutputPort(1).Data;




