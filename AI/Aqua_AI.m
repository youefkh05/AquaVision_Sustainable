function AquaVisionChat()
    clc;
    clear;
    disp("🐟 AquaVision AI");
    disp("Type 'exit' to quit.\n");

    while true
        userInput = lower(input("You: ", 's'));

        if strcmp(userInput, 'exit')
            disp("AquaVision: Goodbye! Stay efficient 🐠");
            break;
        end

        handleInput(userInput);
    end
end

function handleInput(userInput)
    if contains(userInput, 'water')
        sendRandomMessage(waterMessages());
        value = randi([0, 35]); % Simulated value
        printSensorReading(value, 2);
    elseif contains(userInput, 'ph')
        sendRandomMessage(phMessages());
    elseif contains(userInput, 'temp')
        value = randi([20, 35]); % Simulated value
        sendRandomMessage(temperatureMessages());
        printSensorReading(value, 1);
    elseif contains(userInput, 'hi') || contains(userInput, 'hello')
        sendRandomMessage(welcomeMessages());
    elseif contains(userInput, 'sensor')
        % Simulate sensor input for demonstration
        value = randi([20, 35]); % Simulated value
        type = randi([1, 3]);    % Random sensor type
        printSensorReading(value, type);
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
            fprintf("AquaVision: Temperature reading is: %d °C\n", value);
        case 2
            fprintf("AquaVision: Water level 1 reading is: %d cm\n", value);
        case 3
            fprintf("AquaVision: Water level 2 reading is: %d cm\n", value);
        otherwise
            fprintf("AquaVision: Unknown sensor type. Value: %d\n", value);
    end
end

% === Message Definitions ===
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
