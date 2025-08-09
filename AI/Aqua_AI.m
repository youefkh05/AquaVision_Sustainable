clear;
clc;
esp = serialport("COM6", 9600);
configureTerminator(esp, "LF");
flush(esp);

disp("🐟 AquaVision System Started!");

level1 = NaN;
tempValue = NaN;


while true
    if esp.NumBytesAvailable > 0
        rawLine = readline(esp);
        if ~isempty(rawLine) && ~ismissing(rawLine)
            line = strtrim(rawLine);  % Clean line

            if startsWith(line, "Water Level 1")
                level1 = extractValue(line);

                % Read next lines if available
                if esp.NumBytesAvailable > 0
                    line2 = strtrim(readline(esp));  % Water Level 2
                    level2 = extractValue(line2);
                else
                    continue;
                end

                if esp.NumBytesAvailable > 0
                    line3 = strtrim(readline(esp));  % Temperature
                    tempValue = extractValue(line3);
                else
                    continue;
                end

                % Skip Firebase upload success lines
                while esp.NumBytesAvailable > 0
                    extraLine = strtrim(readline(esp));
                    if contains(extraLine, "Uploaded Successfully")
                        break;
                    end
                end

                % Display values
                fprintf("Readings -> L1: %.2f | L2: %.2f | Temp: %.2f\n", ...
                    level1, level2, tempValue);

                % Optionally 
                %AquaVisionChat(level1, tempValue);
            else
                
            end
        end
        AquaVisionChat(level1, tempValue);
        %fprintf("%s\n", line); % Print other lines
    end

    pause(1); % reduce loop CPU usage
end

%% === AI FUNCTIONALITY ===


function val = extractValue(line)
    % Helper function to extract numeric value from "Key: Value" format
    tokens = split(line, ":");
    if numel(tokens) == 2
        val = str2double(strtrim(tokens{2}));
    else
        val = NaN;
    end
end

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
