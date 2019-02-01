<?php

function sendNotification($ProductID, $message) {
   if($ProductID == "ABCD1234EFGH5678") {
      mail("8052318038@vzwpix.com","Hydroponic System Alert",$message);
   }
}

?>
