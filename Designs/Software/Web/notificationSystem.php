<?php

function sendNotification($ProductID, $message, $conn) {
   if($ProductID == "ABCD1234EFGH5678") {
      $settingsData = [];
      $sql = "SELECT * FROM `MachineConfig` WHERE `MachineConfig`.`ProductID`='ABCD1234EFGH5678'";
      $result = mysqli_query($conn,$sql);
      if(!$result) {
         die('Could not get data: ' . mysqli_error($conn));
      }
      while($row=mysqli_fetch_array($result,MYSQLI_ASSOC)) {
         $settingsData["phoneStr"] = $row["phoneStr"];
         $settingsData["carrierStr"] = $row["carrierStr"];
         $settingsData["emailStr"] = $row["emailStr"];
      }
      $phoneStr = str_replace('-','',$settingsData["phoneStr"]);
      // Text
      mail($phoneStr . $settingsData["carrierStr"],"Hydroponic System Alert",$message);
      // Email
      mail($settingsData["emailStr"],"Hydroponic System Alert",$message);
   }
}

?>
