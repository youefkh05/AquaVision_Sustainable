net = resnet18;  
I = imread('fish.jpg');  
I = imresize(I, [224 224]);  
label = classify(net, I);  
disp(label);
