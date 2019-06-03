<?php
session_start();
if(!$_SESSION['isLoggedIn']) {
  header("Location: /login.php");
  die();
}


include "dbinfo.php";

$sql = 'UPDATE `MachineConfig` SET ';
foreach ($_POST as $key => $value) {
   // echo $key, "=", $value, "\n";
   if((double)$value > 0){
      $sql .= "`" . mysqli_real_escape_string($conn,$key) . "` = '" . ((double)$value) . "', ";
   }
}
$sql = substr($sql, 0, -2);
$sql .= " WHERE `ProductID` = '" . mysqli_real_escape_string($conn,$_POST['ProductID']) . "'";

// echo "\nSql: " . $sql . "\n";


$result = mysqli_query($conn,$sql);
if(!$result) {
 die('Could not get data: ' . mysqli_error($conn));
}

echo "success";
?>
