This project simulated a time clock which displayed time in both twelve and twenty-four hour formats, and allowed someone to increment the time in units of hours, minutes, or seconds. I believe that I organized and delineated the various functions in a clean and sensible manner. I also considered many edge cases in my increment_time function. In terms of what I could do better, I really liked how I included a Period enum to make the code easier to read, but if I had more time, I would have written a whole time class that handled time changes behind the scenes. That kind of code is distracting, and should never clutter the purpose of your main file. The most challenging code to write here was the input code, due to the fact that I had to convert strings to integers and ensure that they were within acceptable bounds. I had to search the internet to find the right way to split on a delimiter in C++. Stackoverflow was incredibly helpful in this regard. All the skills I used in this project are transferable. Type conversions, input handling, bounds checking... these are skills which will be repeatedly used throughout my future career. I tried to make this program maintainable and adaptable by keeping it modular, splitting the main functionality into relatively short functions that handled one specific task. In a higher level language it would have been easier to keep functions simple and clean, but I did a reasonable job for a language as verbose as C++.