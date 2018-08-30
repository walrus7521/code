<html>

<form method="post" action="<?php echo $_SERVER['SELF']; ?>">

<p>
What Day?
<select name="formDayOfWeek">
  <option value="">Select...</option>
  <option selected="selected" value="All">All</option>
  <option value="Monday">Monday</option>
  <option value="Tuesday">Tuesday</option>
  <option value="Wednesday">Wednesday</option>
  <option value="Thursday">Thursday</option>
  <option value="Friday">Friday</option>
  <option value="Saterday">Saturday</option>
  <option value="Sunday">Sunday</option>
</select>

Time of Day?
<select name="formTimeOfDay">
  <option value="">Select...</option>
  <option selected="selected" value="All">All</option>
  <option value="Morning">Morning</option>
  <option value="Mid-Day">Mid-Day</option>
  <option value="Early Evening">Early Evening</option>
  <option value="Night">Night</option>
</select>
</p>

<p>
Place of Meeting?
<select name="formPlaceOfMeeting">
  <option value="">Select...</option>
  <option selected="selected" value="All">All</option>
  <option value="Bellevue">Bellevue</option>
  <option value="Bothell">Bothell</option>
  <option value="Carnation">Carnation</option>
  <option value="Duvall">Duvall</option>
  <option value="Fall City">Fall City</option>
  <option value="Issaquah">Issaquah</option>
  <option value="Kenmore">Kenmore</option>
  <option value="Kirkland">Kirkland</option>
  <option value="Mercer Island">Mercer Island</option>
  <option value="North Bend">North Bend</option>
  <option value="Preston">Preston</option>
  <option value="Redmond">Redmond</option>
  <option value="Sammamish">Sammamish</option>
  <option value="Snoqualmie">Snoqualmie</option>
  <option value="Woodinville">Woodinville</option>
</select>

</p>

<p>
Type of Meeting?
</p>
<p>
<Input type = 'Radio' Name ='gender' value= 'male'> Men only
<Input type = 'Radio' Name ='gender' value= 'female'> Women only
<Input type = 'Radio' Name ='gender' value= 'all' checked> All
</p>

<p>
<Input type = 'Radio' Name ='attendees' value= 'open'> Open, anybody can attend
<Input type = 'Radio' Name ='attendees' value= 'closed'> Closed, AA members only*
<Input type = 'Radio' Name ='attendees' value= 'all' checked> All
</p>

<p>
Additional options
</p>
<p>
<Input type = 'Checkbox' Name ='childcare' value ="childcare" >Childcare
<Input type = 'Checkbox' Name ='stepper' value="stepper" >Step study or Big Book Study
<Input type = 'Checkbox' Name ='spanish' value="spanish" >Spanish speaking
<p>
<Input type = 'Checkbox' Name ='handicap' value="handicap" >Handicapped Access
<Input type = 'Checkbox' Name ='gay' value="gay" >Gay & Lesbian
<Input type = 'Checkbox' Name ='young' value="young" >Young People
</p>

<p>
<input name="Search" type="submit" value="Search!">
</p>
</form>

<table border=0>
<tr><td valign="top">

<?php
    $g_server = '192.168.13.33';
    $g_user = 'esig';
    $g_pass = 'billw417';
    $g_db = 'Meetings';

    $g_Day = $_POST['formDayOfWeek'];
    $g_Time =  $_POST['formTimeOfDay'];
    $g_Place = $_POST['formPlaceOfMeeting'];
    $g_Gender = $_POST['gender'];
    $g_Attendees = $_POST['attendees'];
    $g_Childcare = $_POST['childcare'];
    $g_Stepper = $_POST['stepper'];
    $g_Spanish = $_POST['spanish'];
    $g_Handicap = $_POST['handicap'];
    $g_Gay = $_POST['gay'];
    $g_Young = $_POST['young'];

    $days = array('Monday', 'Tuesday', 'Wednesday', 'Thursday','Friday', 'Saterday', 'Sunday');
    $header = "<tr><td><b><u>Day</u></b></td><td><b><u>Time</u></b></td><td><b><u>City</u></b></td><td><b><u>Meeting Name: Location and Address</u></b></td></tr>";

    $format_map_only = "<tr><td> %s </td> <td> %s </td> <td> %s </td> <td> <b>%s</b> %s %s, %s, %s %s %s</td></tr>";
    $format_map_and_mt = "<tr><td> %s </td> <td> %s </td> <td> %s </td> <td> <b>%s</b> %s %s, %s, %s %s  <b>[%s]</b> %s</td></tr>";

//<p style="color:red">This is some text!</p>
//<font color="red">This is some text!</font> 

function connect_dbs() {
    global $g_server;
    global $g_user;
    global $g_pass;
    global $g_db;
    $sqli = new mysqli($g_server, $g_user, $g_pass, $g_db);
    if ($sqli->connect_errno) {
        printf("Connect failed: %s\n", $sqli->connect_error);
        exit();
    } else {
        //printf("woo hooo !!!!\n");
    }
    $sqli->select_db($g_db);
    return $sqli;
}

function disconnect_dbs($sqli)
{
    $sqli->close();
}

function show_header() {
    global $header;
    echo $header;
}

function show_row($row) {
    global $format_map_only, $format_map_and_mt, $g_Time;
    $day_row = "";

    $time_input = $row[10];
    $strtotime = strtotime($time_input);

    $the_time = date("g:iA", $strtotime);

    $street = $row[5];
    $city   = $row[6];
    $state  = $row[7];
    $zip    = $row[8];
    $mt     = $row[9];

    //$url = "http://www.google.com/#output=search&q=11224+SE+76th+St+Newcastle+WA+98056&//oq=11224+SE+76th+St+Newcastle+WA+98056&";\
    //$url = "http://www.google.com/#output=search&sclient=psy-ab&q=$street+$city+$state+$zip&//oq=$street+$city+$state+$zip&";
    //$url = "http://www.google.com/#hl=en&q=$street+$city+$state+$zip&//oq=$street+$city+$state+$zip&";
    $url = "http://www.google.com/#output=search&q=$street+$city+$state+$zip&oq=$street+$city+$state+$zip&";

    //$map = "<P><A HREF=\"$url\">Map</A>";
    $map = "<P><A HREF=\"$url\" target=\"_blank\">Map</A>";

    if (strlen($mt) == 0) {
        $day_row = sprintf($format_map_only, $row[0], $the_time, $row[2], $row[3], $row[4], $street, $city, $state, $zip, $map);
    } else {
        $day_row = sprintf($format_map_and_mt, $row[0], $the_time, $row[2], $row[3], $row[4], $street, $city, $state, $zip, $mt, $map);
    }

    if ($g_Time == 'All') {
        $start_time = 0;
        $end_time  = strtotime("11:59 PM");
    } elseif ($g_Time == 'Morning') {
        $start_time = 0;
        $end_time  = strtotime("10:00 AM");
    } elseif ($g_Time == 'Mid-Day') {
        $start_time = strtotime("10:00 AM");
        $end_time  = strtotime("2:00 PM");
    } elseif ($g_Time == 'Early Evening') {
        $start_time = strtotime("3:00 PM");
        $end_time  = strtotime("6:00 PM");
    } elseif ($g_Time == 'Night') {
        $start_time = strtotime("6:30 PM");
        $end_time  = strtotime("11:59 PM");
    } else {
        $start_time = 0;
        $end_time  = strtotime("11:59 PM");
    }

    if (($strtotime > $start_time) && ($strtotime < $end_time)) {
        echo $day_row;
    }
}


function get_day($ui) {
    $day = "";
    if      (eregi('sa', $ui)) $day = 'Saterday';
    else if (eregi('su', $ui)) $day = 'Sunday';
    else if (eregi('mo', $ui)) $day = 'Monday';
    else if (eregi('tu', $ui)) $day = 'Tuesday';
    else if (eregi('we', $ui)) $day = 'Wednesday';
    else if (eregi('th', $ui)) $day = 'Thursday';
    else if (eregi('fr', $ui)) $day = 'Friday';
    else                       $day = 'All';
    return $day;
}

function dump_table($sqli, $table_name, $city, $time) {
    if (strcmp($city, "*") == 0) {
        $sql = "SELECT * FROM $table_name WHERE 1 ORDER BY PLAY ASC";
    } else {
        $sql = "SELECT * FROM $table_name WHERE City like '%$city%' ORDER BY PLAY ASC";
    }
    //printf("dump_table: sql %s\n", $sql);
    //if ($result = $sqli->query("SELECT * FROM $table_name WHERE City='$city'")) {
    if ($result = $sqli->query($sql)) {
        while ($row = $result->fetch_row()) {
            show_row($row);
        }
    } else {
        //printf("failed query\n");
    }
}

?>

<?php

    echo $g_Gender;
    echo $g_Attendees;

    echo $g_Childcare;
    echo $g_Stepper;
    echo $g_Spanish;
    echo $g_Handicap;
    echo $g_Gay;
    echo $g_Young;




    $day  = $g_Day;
    $time = $g_Time;
    $city = $g_Place;
    if (strlen($day) == 0) {
        $day = 'All';
    }
    if (strlen($city) == 0) {
        $city = '*';
    }
    $sqli = connect_dbs();
    show_header();
    $the_day = $day;
    if ($the_day == 'All') {
        foreach ($days as $day) {
            dump_table($sqli, $day, $city, $time);
        }
    } else {
        dump_table($sqli, $the_day, $city, $time);
    }
    disconnect_dbs($sqli);
?>

</td></tr>
</table>

</html>
