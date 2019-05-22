<?php

function sendNotification($ProductID, $message) {
   if($ProductID == "ABCD1234EFGH5678") {
      // Text
      mail("8052318038@vzwpix.com","Hydroponic System Alert",$message);
      // Email
      mail("jaaking@ucsc.edu","Hydroponic System Alert",$message);
   }
}

?>
