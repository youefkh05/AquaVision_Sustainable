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

% Last Modified by GUIDE v2.5 09-Aug-2025 20:48:21

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


% global variables
global level1       %water level at aqua 1
global temperature1 %temperature at aqua1
global esp

    %initialize the variable
    level1 = 0;
    temperature1 = 0;
    set(handles.status_text, 'String', 'Not Connected');

    % List available serial ports
    availablePorts = serialportlist("available");

    % Desired port
    targetPort = "COM9";

    % Update handles structure
    guidata(hObject, handles);
    
    
    % Keep static label fixed
    set(handles.Mes_stat_box, 'String', sprintf('\nLevel1\n\n\nTemperature'));
   
    
    while true
        if any(strcmpi(availablePorts, targetPort))
            delete(instrfind); % clear any previous COM objects
            disp("✅ COM9 is available, connecting...");
            % Connect to ESP32
            esp = serialport(targetPort, 9600);
            configureTerminator(esp, "LF");
            flush(esp);
            % Start loop to read ESP32 data
            while isvalid(esp)
                rawLine = readline(esp);
                line = strtrim(rawLine);  % Clean line
                fprintf("%s\n", line); % Print other lines
                pause(1);
            end % while isvalid(esp)
        end % if any(strcmpi(availablePorts, targetPort))
        
        set(handles.status_text, 'String', 'Not Connected');
        pause(1);
    end % while true
        
end
% UIWAIT makes AquaVision_Front wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = AquaVision_Front_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
end



function AI_In_Callback(hObject, eventdata, handles)
% hObject    handle to AI_In (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of AI_In as text
%        str2double(get(hObject,'String')) returns contents of AI_In as a double
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
