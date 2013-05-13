ofxChart
========
Introduction
------------
ofxChart is a custom add-on for OpenFrameworks C++ library. It allows adding various 2d and 3d charts to your projects. You can create individual charts independently or use ofxChart class as a manager. Current architecture allows adding as many Data Series to your axis sets as desired and performance on mobile devices is far superior to existing Core Plot due to optimizations with ofFBO and OpenGL rather than relying on Quartz. 

Licence
-------
The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).  
Copyright (c) 2013 Sergey Yershov, fulltrend@hotmail.com

Usage
------------
You can simply add all your axes containers via ofxChart class or instantiate them independently. ofxChart architecture allows you to add unlimited Axis Sets (containers) to your project. There are 3 types currently - single (for charts, like Pie, Dohnut), 2d (X,Y) and 3d (X,Y,Z). Each axis set can have unlimited number of corresponding Data Series. And each Data Series can have an unlimited number of corresponding data points. 

Current Features
------------
- All instances are templates to maintain integrity of data sets for each set. The following data types are supported (int, short, float, double, Poco::DateTime)
- Following Chart Types added: Pie Chart, 2d/3d line chart, point chart, area chart, 2d/3d area range, bar and column range, 2d stock charts
- Chart Container allows scaling and offsetting inside local space
- Static and dynamic axis positioning with customizable axis crossing. Axis label formatting and positioning
- Adjust data point colors, relative dimensions
- Tested on VS2010/VS2008, OS/X and IOS, Android. Earliest OF release supported: 0073 (can be supported on 0072 with ofxFBO)



Examples
------------
Copy the library  to your /addons folder. There are 3 examples:
- 2d Stock Chart. Allows you to switch between candlestick and bar chart. Also, shows how to use individual charts independent of ofxChart main class.
- 2d Sine Wave mobile example. Double-tap to switch between line and area charts
- 3d Example. 3d bar range chart and 3d pie chart. Use controls and mouse to rotate/scale/shift


Collaboration and Future Enhancement
------------
I am actively seeking collaborators with expertise in OpenGL and 3d graphics, geometry/statistics, OF, or any other useful skills to add to this project. I would like ofxChart to become one of the most useful add-ons for the most useful framework out there. 
This is the initial release. Near future enhancements include adding event handling, displaying labels and generating legend. Further works will include more chart types and gages.

Version
------------
- Version 1.0 (05/13/2013)
