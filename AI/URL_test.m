clear;
clc;
while true
    sendSensorDataToFirebase(15, 30, 10, 30);
    pause(0.5);
end


function sendSensorDataToFirebase(depth1, temp1, depth2, temp2)
    % === Your Firebase details ===
    databaseURL = 'https://project-0-51c9c-default-rtdb.firebaseio.com';
    path = '/sensors/data.json'; % Firebase node
    % If your Firebase rules require authentication, add '?auth=YOUR_ID_TOKEN'
    
     % Get current time and date
    nowTime = datetime('now', 'TimeZone', 'local');
    timeStr = datestr(nowTime, 'HH:MM:SS');   % e.g., "14:23:45"
    dateStr = datestr(nowTime, 'yyyy-mm-dd'); % e.g., "2025-08-09"


    % Prepare the JSON structure
    dataStruct.time = timeStr; % Placeholder for timestamp
    dataStruct.date = dateStr; % Replace with dynamic date if needed
    dataStruct.depth1 = depth1;
    dataStruct.temp1 = temp1;
    dataStruct.depth2 = depth2;
    dataStruct.temp2 = temp2;
    dataStruct.source = 'AquaVision App';

    % Convert struct to JSON
    jsonData = jsonencode(dataStruct);

    % Send HTTP POST request (Firebase push equivalent)
    options = weboptions('MediaType', 'application/json', 'Timeout', 10);
    try
        response = webwrite([databaseURL, path], jsonData, options);
        disp('✅ JSON Data Uploaded Successfully!');
        disp(response);
    catch ME
        warning('❌ Failed to upload JSON: %s', ME.message);
    end
end
