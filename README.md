# Links to Practical Videos

*Practical #1: How to install the Ubuntu subsystem for Windows 10*  https://www.youtube.com/watch?v=22VtIhzPB1o

*Timestamp for quick RootEffi demo*  https://www.youtube.com/watch?v=22VtIhzPB1o&t=3070s

*Practical #2: Plotting data with Python and xmgrace*  https://www.youtube.com/watch?v=KrcyFavMHiY

*Practical #3: Detector Efficiency and Peak Fitting*  https://www.youtube.com/watch?v=OG-s4FhOMIk

*Practical #4: Semi-Empirical Mass Formula* https://www.youtube.com/watch?v=B2W0OYhtddY


# Detection efficiency calibration of germanium detectors in ROOT

**Link to RootEffi video:** 

The script includes the instructions on how to run it in ROOT/GRSISort.

It has many commented lines to walk you through the script.

It also includes several (optional) formatting commands with which you should familiarize yourself.

The goal of this script is to get an efficiency fit for your data set, and also to get familiar with ROOT scripts/macros.

# Download RootEffi

To install git, paste in your terminal:

    sudo apt-get install git

To download RootEffi, paste:

    git clone https://github.com/UWCNuclear/RootEffi.git

To run RootEffi, type in the command line:

     grsisort -l RootEffi.C

or:

    grsisort -l
    
and then the following line in the GRSISort terminal:

    .x RootEffi.C

Also, the above 'grsisort' can be replaced with 'root' - and it should work just fine!

Also, it seems that this script prefers ROOT6.

# Using RootEffi

To use RootEffi, you need the area (number of counts) of the most intense peaks from your calibration source(s), and the uncertainty on the area of those peaks.

For an absolute efficiency calibration, you will also need the original activity of the calibration source(s), the date of the calibration run(s), and the length of calibration run(s) (in seconds).

Then, you have to edit these values in RootEffi.C.

Whenever you edit a script, you should save it and close ROOT/GRSISort to run it again.

RootEffi.C is set up to do an absolute or relative detection efficiency fit using the germanium efficiency equation from Knoll.

The Radware equation is also in there, but it hasn't been tested.

Ran as is, RootEffi does a relative efficiency curve using the Knoll equation.

To do an absolute efficiency fit, you have to comment out (//  ...) the absolute efficiency lines and uncomment the relative efficiency lines.

To use the Radware equation, you have to comment out the Knoll lines (/*  ...  */) and uncomment the Radware lines.

And you are ready to use your new efficiency calibration!
