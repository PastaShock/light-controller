# Light-controller
George Pastushok 2022

## About

This is a LAMP stack project for me to learn about how to create and manage a website using Apache, MySQL and PHP. 

### What is it?

This is a project that is supposed to take an input from a user (at first boolean, later four sets of 8 bit values) and send that to an ESP32 that is on my network listening at a certain port.

The ESP32 should be sending back its current state periodically to let the DB know whether it is on, off or its RGBA values.

The website should eventually have acolor picker to set the RGB values and a brightness slider to set A value. 

I want to add Bootstrap.css styling to make my life a bit easier and maybe throw in a modal for fun

### currently:

The site only has a toggle slider and it doesn't use any CSS libraries. 

The current state is non-exitent, the site always loads a default 0 value

the toggle is not automatic, a submit button must be pressed to get it to send.
