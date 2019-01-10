<?php
session_start();
$_SESSION["isLoggedIn"] = false;
header("Location: /index.php");
die();
?>
