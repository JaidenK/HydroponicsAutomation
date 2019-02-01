<?php
session_start();
if(!$_SESSION['isLoggedIn']) {
  header("Location: /login.php");
  die();
}


// the message
$msg = "First line of text\nSecond line of text";

// use wordwrap() if lines are longer than 70 characters
$msg = wordwrap($msg,70);

// send email
mail("8052318038@vzwpix.com","Testing From Ballistaline",$msg);
?>
