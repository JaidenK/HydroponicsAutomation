<?php
session_start();
if(!$_SESSION['isLoggedIn']) {
  header("Location: /login.php");
  die();
}

include "dbinfo.php";
include "notificationSystem.php";

if($_GET['TestNotify']=='1') {
   sendNotification("ABCD1234EFGH5678", "This is a test of the notification system.",$conn);
   die("notified");
}

$sql = 'UPDATE `MachineConfig` SET ';

if(array_key_exists("phone", $_POST)) {
   $sql .= '`phoneStr`=\''.mysqli_real_escape_string($conn,$_POST['phone']).'\', ';
}
if(array_key_exists("carrier", $_POST)) {
   $sql .= '`carrierStr`=\''.mysqli_real_escape_string($conn,$_POST['carrier']).'\', ';
}
if(array_key_exists("email", $_POST)) {
   $sql .= '`emailStr`=\''.mysqli_real_escape_string($conn,$_POST['email']).'\', ';
}

$sql = substr($sql, 0, -2); // Trim trailng ", "
$sql .= " WHERE `ProductID` = 'ABCD1234EFGH5678'";

$result = mysqli_query($conn,$sql);
if(!$result) {
  echo "POST: " . serialize($_POST) . "      ";
  echo "SQL: " . $sql . "      ";
  die('Could not update data: ' . mysqli_error($conn));
}

sendNotification("ABCD1234EFGH5678", "Updates on your hydroponics system are now being sent to " . $_POST['phone'] . " and " . $_POST['email'] . ".",$conn);

echo "success";
?>
