clear;
clc;
esp = serialport("COM9", 9600);
configureTerminator(esp, "LF");
flush(esp);

disp("🐟 AquaVision System Started!");

while true
    % === Read 4 lines from ESP32 ===
    readline(esp);                         % Blank line
    levelLine = readline(esp);             % Middle Water Level
    tempLine = readline(esp);              % Water Temperature
    statusLine = readline(esp);            % Send Status

    % === Parse values ===
    levelValue = sscanf(levelLine, 'Middle Water Level: %f');
    tempValue  = sscanf(tempLine, 'Water Temprature: %f');
    %status     = strtrim(erase(statusLine, 'Send Status:'));

    % === Display sensor readings ===
    fprintf('\n📊 ESP32 Sensor Report:\n');
    fprintf('  Water Level   = %.2f cm\n', levelValue);
    fprintf('  Temperature   = %.2f °C\n', tempValue);
    fprintf('  Send Status   = %s\n\n', status);

    % === Call chatbot for user input ===
    AquaVisionChat(levelValue, tempValue);
    
    pause(1); % optional: reduce loop speed
end

%% === CHATBOT FUNCTIONALITY ===

function AquaVisionChat(levelValue, tempValue)
    userInput = lower(input("You: ", 's'));

    if strcmp(userInput, 'exit')
        disp("AquaVision: Goodbye! Stay efficient 🐠");
        return;
    end

    handleInput(userInput, levelValue, tempValue);
end

function handleInput(userInput, levelValue, tempValue)
    if contains(userInput, 'water')
        sendRandomMessage(waterMessages());
        printSensorReading(levelValue, 2);
    elseif contains(userInput, 'temp')
        sendRandomMessage(temperatureMessages());
        printSensorReading(tempValue, 1);
    elseif contains(userInput, 'ph')
        sendRandomMessage(phMessages());  % Simulated
    elseif contains(userInput, 'hi') || contains(userInput, 'hello')
        sendRandomMessage(welcomeMessages());
    elseif contains(userInput, 'sensor')
        printSensorReading(tempValue, 1);
        printSensorReading(levelValue, 2);
    else
        disp("AquaVision: I'm still learning. Try asking about 'water', 'pH', or 'temperature'.");
    end
end

function sendRandomMessage(messages)
    idx = randi(length(messages));
    fprintf("AquaVision: %s\n", messages{idx});
end

function printSensorReading(value, type)
    switch type
        case 1
            fprintf("AquaVision: Temperature reading is: %.2f °C\n", value);
        case 2
            fprintf("AquaVision: Water level is: %.2f cm\n", value);
        case 3
            fprintf("AquaVision: Water level 2 reading is: %.2f cm\n", value);
        otherwise
            fprintf("AquaVision: Unknown sensor type. Value: %.2f\n", value);
    end
end

%% === CHAT MESSAGES ===
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
