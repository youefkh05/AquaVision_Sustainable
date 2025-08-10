function varargout = AquaVision_Front(varargin)
%deploytool  guide
% AQUAVISION_FRONT MATLAB code for AquaVision_Front.fig
%      AQUAVISION_FRONT, by itself, creates a new AQUAVISION_FRONT or raises the existing
%      singleton*.
%
%      H = AQUAVISION_FRONT returns the handle to a new AQUAVISION_FRONT or the handle to
%      the existing singleton*.
%
%      AQUAVISION_FRONT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in AQUAVISION_FRONT.M with the given input arguments.
%
%      AQUAVISION_FRONT('Property','Value',...) creates a new AQUAVISION_FRONT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before AquaVision_Front_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to AquaVision_Front_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help AquaVision_Front

% Last Modified by GUIDE v2.5 10-Aug-2025 22:31:30

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @AquaVision_Front_OpeningFcn, ...
                   'gui_OutputFcn',  @AquaVision_Front_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT
end

% --- Executes just before AquaVision_Front is made visible.
function AquaVision_Front_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to AquaVision_Front (see VARARGIN)

% Choose default command line output for AquaVision_Front
handles.output = hObject;

%imgae back ground
ah=axes('unit','normalized','position',[0 0 1 1]);
bg=imread("Fish_Sesnor.png");
imagesc(bg);
set(ah,'handlevisibility','off','visible','off');

pause(2);

    % Initialize variables
    handles.level1 = 0;
    handles.temperature1 = 0;
    handles.targetPort = "COM9";
    handles.esp = [];
    set(handles.status_text, 'String', 'Not Connected');
    set(handles.Mes_stat_box, 'String', sprintf('\nLevel1\n\n\nTemperature'));
    set(handles.Mes_variable, 'String', sprintf('\n%.2f m\n\n\n%.2f °C', ...
    handles.level1, handles.temperature1));
    set(handles.AI_Out, 'String', sprintf("I m Waiting"));
    
    
    % Create a timer for reading ESP32 data
    handles.t = timer( ...
        'ExecutionMode', 'fixedSpacing', ...
        'Period', 3, ... % check every 3 second
        'TimerFcn', @(~,~)readESP32(hObject) ...
    );
    
    % Update handles structure
    guidata(hObject, handles);
    
    % Start the timer
    start(handles.t);

end
% UIWAIT makes AquaVision_Front wait for user response (see UIRESUME)
% uiwait(handles.figure1);


function readESP32(hObject)
 
    % If the figure was closed, exit immediately
    if ~ishandle(hObject)
        return;
    end
    
    handles = guidata(hObject);
    disp("Read ESP");
    
    %also exit if figure UserData says it's closing
    if isappdata(hObject, 'closing') && getappdata(hObject, 'closing')
        disp("Exit close esp");
        return;
    end
    
    try
        % If ESP not connected, try to connect
        if isempty(handles.esp) || ~isvalid(handles.esp)
            availablePorts = serialportlist("available");
            if any(strcmpi(availablePorts, handles.targetPort))
                delete(instrfind); % clear any lingering serial objects
                disp("✅ COM9 is available, connecting...");
                handles.esp = serialport(handles.targetPort, 9600);
                configureTerminator(handles.esp, "LF");
                flush(handles.esp);
                set(handles.status_text, 'String', 'Monitoring started...');
                guidata(hObject, handles);
            else
                set(handles.status_text, 'String', 'Not Connected');
                disp("Not Connected");
                return;
            end
        end

        
        % If connected, try to read
        if isvalid(handles.esp) && handles.esp.NumBytesAvailable > 0
            rawLine = readline(handles.esp);
            if ~isempty(rawLine) && ~ismissing(rawLine)
                set(handles.status_text, 'String', 'Connected');
                line = strtrim(rawLine);

                % Check for water level line
                if startsWith(line, "Middle Water Level")
                    handles.level1 = extractValue(line);

                    % Read temperature line if available
                    if handles.esp.NumBytesAvailable > 0
                        tempLine = strtrim(readline(handles.esp));
                        if startsWith(tempLine, "Water Temprature") % ESP spelling
                            handles.temperature1 = extractValue(tempLine);
                        end
                    end

                    % Update GUI variable box
                    set(handles.Mes_variable, 'String', ...
                        sprintf('\n%.2f m\n\n\n%.2f °C', ...
                        handles.level1, handles.temperature1));

                    guidata(hObject, handles);
                end
            end
        end
        
    catch ME
        warning("⚠ Error reading ESP32: %s", ME.message);
        % If error, mark as disconnected so it will retry
        if isvalid(handles.t) 
            stop(handles.t);
            start(handles.t);
        end
        handles.esp = [];
        set(handles.status_text, 'String', 'Not Connected');
        guidata(hObject, handles);
    end
end

% Helper function to parse numeric values
function val = extractValue(line)
    tokens = regexp(line, '([-+]?[0-9]*\.?[0-9]+)', 'match');
    if ~isempty(tokens)
        val = str2double(tokens{1});
    else
        val = NaN;
    end
end


% --- Executes when user attempts to close figure ---
function figure1_CloseRequestFcn(hObject, eventdata, handles)
    % Mark as closing
    setappdata(hObject, 'closing', true);
    disp("Exit close figure1");

    try
        if isfield(handles, 't') && isvalid(handles.t)
            stop(handles.t);
            delete(handles.t);
            disp("Timer is stopped");
        end
        if isfield(handles, 'esp') && ~isempty(handles.esp) && isvalid(handles.esp)
            clear handles.esp;
        end
    catch
    end
    delete(hObject);
end


% --- Outputs from this function are returned to the command line.
function varargout = AquaVision_Front_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
end


% --- Executes during object creation, after setting all properties.
function AI_In_CreateFcn(hObject, eventdata, handles)
% hObject    handle to AI_In (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

function AI_In_Callback(hObject, eventdata, handles)
% hObject    handle to AI_In (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of AI_In as text
%        str2double(get(hObject,'String')) returns contents of AI_In as a double
    % Get user input from edit box
    userInput = lower(get(hObject, 'String'));

    % Clear the edit box after submission
    set(hObject, 'String', '');

    % Call AI handler with latest sensor data
    handleInput(userInput, handles.level1, handles.temperature1, handles);
    
    disp("AI In");
    
    % Save any changes to handles
    guidata(hObject, handles);
end

function handleInput(userInput, levelValue, tempValue, handles)
    disp("AI_Out");
    if strcmp(userInput, 'exit')
        set(handles.AI_Out, 'String', "AquaVision: Goodbye! Stay efficient ");
        return;
    end

    if contains(userInput, 'water')
        msg = sendRandomMessage(waterMessages());
        set(handles.AI_Out, 'String', sprintf("%s\nWater level: %.2f m", msg, levelValue));

    elseif contains(userInput, 'temp')
        msg = sendRandomMessage(temperatureMessages());
        set(handles.AI_Out, 'String', sprintf("%s\nTemperature: %.2f °C", msg, tempValue));

    elseif contains(userInput, 'ph')
        msg = sendRandomMessage(phMessages());
        set(handles.AI_Out, 'String', msg);

    elseif contains(userInput, 'hi') || contains(userInput, 'hello')
        msg = sendRandomMessage(welcomeMessages());
        set(handles.AI_Out, 'String', msg);

    elseif contains(userInput, 'sensor')
        set(handles.AI_Out, 'String', sprintf("Temperature: %.2f °C\nWater Level: %.2f m", ...
            tempValue, levelValue));

    else
        set(handles.AI_Out, 'String', ...
            "AquaVision: I'm still learning. Try asking about 'water', 'pH', or 'temperature'.");
    end
end

function msg = sendRandomMessage(messages)
    idx = randi(length(messages));
    msg = sprintf("AquaVision: %s", messages{idx});
end


%=== CHAT MESSAGES ===
function msgs = welcomeMessages()
    msgs = {
        "Hello, fish farmer!"
        "Welcome to AquaVision!"
        "Nice to see you!"
        "System ready and watching your tank!"
        "Hey there! AquaVision at your service."
        "Good day! Monitoring in progress."
        "Welcome aboard!"
        "Ready to optimize your aquaculture."
        "Sensors are all set."
        "Data flows, AquaVision knows!"
    };
end

function msgs = waterMessages()
    msgs = {
        "Water levels are optimal!"
        "The water is calm and clear."
        "All systems show good water status."
        "Tank water is within safe range."
        "Water conditions are being monitored."
        "H2O is healthy today!"
        "Water quality checks out."
        "Looks like the water is doing fine."
        "No water alerts at the moment."
        "Fish are swimming happy!"
    };
end

function msgs = phMessages()
    msgs = {
        "pH is balanced and healthy."
        "pH levels are looking good!"
        "Current pH: within ideal range."
        "pH sensors report stable readings."
        "No pH issues detected."
        "Aquatic chemistry looks great."
        "All pH systems are green."
        "Fish approve of today's pH!"
        "pH is within the safe zone."
        "Perfect acidity levels right now!"
    };
end

function msgs = temperatureMessages()
    msgs = {
        "Water temperature is stable and ideal."
        "Current temperature: Fish-friendly!"
        "No thermal stress in the tank."
        "Temperature sensors are reporting safe levels."
        "Cool and steady: perfect tank conditions."
        "Heat levels are well regulated."
        "Fish are comfy at this temperature."
        "Tank environment is thermally balanced."
        "No overheating detected."
        "Temperature checks: all clear!"
    };
end
