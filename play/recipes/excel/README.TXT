
                          The Hacker's Diet
                  http://www.fourmilab.ch/hackdiet/
                      Computer Tools User Notes
                             Release 2006

              by John Walker -- http://www.fourmilab.ch/
                           August 3rd, 2006

This directory contains  the  computer  tools  which  supplement  "The
Hacker's  Diet".   All of the files are worksheets and charts intended
for use with Microsoft Excel 2003, running under Microsoft Windows  XP
or above.

Excel  files  are  putatively  compatible  between  Windows  and   the
Macintosh,  but  if  you  move  these  files  to  the Macintosh you'll
probably have to change the handling of dates and  times  and  correct
(or  ignore)  some  subtle  incompatibilities  between  the ISO 8859/1
Latin-1 character set used by Windows and the Apple-specific character
set  used on the Macintosh.  I have not personally tested any of these
files on the Macintosh.

Microsoft's record for upward compatibility from release to release of
Excel over the last decade is so wretched it is difficult to attribute
to  mere incompetence, although that is much in evidence as well.  The
macros associated with the various worksheets in this package are, for
the  most  part, quite straightforward compared to a typical corporate
Excel application.  Yet  they  have  broken  in  almost  every  single
release  of  Excel  since  2.0  (on which they were developed), and in
every case due to a gratuitous incompatible change,  not  possible  to
compensate  for  in  a manner which works on earlier releases.  I deem
this "strategic incompatibility"--by  deliberately  destabilising  the
original  macro  language  (in  which Microsoft's customer base has an
investment approaching  a  billion  dollars),  they  force  people  to
"upgrade"   to   the   even   less   compatible   Visual  Basic  macro
language--discarding perfectly working code and reimplementing  it  in
an  opaque  and  unstable  language  for the convenience of Microsoft.
Convenience...and profitability--by making macros  non-portable  among
Excel  releases,  they  force  a  customer  who  wishes  to deploy one
application which counts on features in a new release to "upgrade" all
machines  to  the  new  release  in  order  to maintain macro and data
compatibility.  All of which is to say that you shouldn't be surprised
if  one  or  more of these macros break when the next "enhancement" to
Excel rolls out.  If  you  aren't  inclined  to  dig  in  and  fix  it
yourself,  you'll  have to wait until an updated version is available,
or else use the Pencil and Paper alternatives given in the book.

                      Files In This Distribution
                      --------------------------

    ACAD.xls        Autodesk,  Inc.   stock  price database.  (Used to
                    create the charts in the Moving  Averages  section
                    of Chapter 5 (Signal and Noise).

    ACADma.xlc      Chart  of  stock  price  with moving average which
                    appears in the same section.

    ACADma.xls      Moving average database charted by ACADma.xls.

    ACADstok.xlc    Chart of raw stock price.

    Bestfit.xls     Trend fitting lab.  See the "Trying trend fitting"
                    section  at  the  end  of  Chapter  5  (Signal and
                    Noise).

    Exerplan.xls    Exercise plan "Ladders" from Chapter 8  (What,  Me
                    Exercise?) in Excel.

    Feedlab.xls     Feedback lab.  See the "Fun with Feedback" section
                    at the end of Chapter 4 (Food and Feedback).

    Forecast.xls    Weight loss forecast  worksheet.   See  the  "Diet
                    planning"  section  in  Chapter 9 (Losing Weight).

    Lifext.xls      Life extension forecasting worksheet.  See "Living
                    longer" in Chapter 6 (What, Me Exercise?).

    Mealplan.xlm    Macros for meal planning.

    Mealplan.xls    Meal  planning  database and worksheet.  See "Meal
                    planning  with  Excel"  in  Chapter  8   (Planning
                    Meals).

    README.TXT      This file.

    Smooth.xls      Moving   averages   lab.   See  "Exploring  moving
                    averages" in Chapter 5 (Signal and Noise).

    Units.xls       Excel database of units and conversion factors  as
                    given in Chapter 12.

    Wategoal.xls    Excel  database  of  optimum  weights  as given in
                    Chapter 9 (Losing  Weight)  and  typical  calories
                    burned  per  day  from Chapter 3 (The Rubber Bag).

    Weighist.xls    Empty  template  for  cumulative  weight   history
                    database.

    Weight.xlm      Macros for weight database management.

    Weigtemp.xls    Template  for  creating  yearly  weight management
                    worksheets.  See Chapter 7 (Weight Monitoring).

                       About "Cell Protection"
                       -----------------------

Most of these worksheets have been  stored  as  "protected  documents"
with  all  cells  not intended for user data entry locked.  Otherwise,
when  working  with  a  complex  worksheet, it's  extremely  easy   to
accidentally  enter  data into an incorrect cell, perhaps destroying a
formula and introducing subtle errors all over the worksheet.  All  of
the protection has been applied with no password; it's purely a way to
prevent  errors,  not  to constrain your freedom to examine and modify
the worksheets if you desire.  You can unprotect any of the worksheets
simply  by  choosing "Tools/Protection/Unprotect Sheet" from the Excel
menu.  None of the formulas used in any of the  worksheets  have  been
hidden;  they  all  appear  in the formula bar when you select a cell.

                          Colours in Charts
                          -----------------

The  charts  created  by  the  weight  management worksheet macros are
"colourised" to render them easier to read and  more  attractive.   If
you  print these charts on a black and white printer, some of the text
may be difficult to read, depending on how your printer handles colour
information.   If  this  causes  a  problem, simply edit the chart and
change all the text and graphics to black  and  backgrounds  to  white
before  printing.   Anyway, it's generally more convenient to file the
charts as Excel .xlc files on your computer and view them  with  Excel
(in full colour) rather than printing them out.   Similarly,  if  your
computer  is equipped with a monochrome screen, you may wish to change
some of the text and background colours in the worksheets  to  improve
legibility.

            Compatibility with Localised Versions of Excel
            ----------------------------------------------

All  of  the  worksheets  and macros were developed using the domestic
U.S. versions of Excel and Windows.   If you use them with versions of
Excel  and  Windows  localised  for other countries, you may encounter
some problems.  All of the macros have been  saved  as  "International
Macro  Sheets",  in which formulas specified by strings are assumed to
be in English.  This generally allows the  worksheets  and  macros  to
function  properly  on  other  language  editions (they work fine, for
example, on  the  French  language  Windows).   Still,  sometimes  one
"little  thing" or another that differs in localised software may trip
you up.  If you encounter problems using these worksheets  and  macros
with localised versions of Windows and  Excel,  you  can  usually  get
around them by configuring your Windows system as close as possible to
a U.S. standard environment with the International tool in the Control
Panel.   Note  that  the formats you configure there for date and time
and decimal points in numbers affect how Excel recognises the type  of
data you enter in a cell.
