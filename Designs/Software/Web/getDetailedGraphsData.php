<?php 





$('#editTargetsForm').submit(function(e){
        // https://www.airpair.com/js/jquery-ajax-post-tutorial
        $("#editTargetsSaveButton").html('Saving...');
        $.post(
          'setTargets.php',
          $(this).serialize(),
          function( data, textStatus, jQxhr ){
            if(data=="success") {
              $("#editTargetsSaveButtonResponse").html("Settings saved!");
              $("#editTargetsSaveButtonResponse").removeClass("text-danger");
              $("#editTargetsSaveButtonResponse").addClass("text-primary");
            }else{
              $("#editTargetsSaveButtonResponse").html("Unable to save settings.");
              $("#editTargetsSaveButtonResponse").addClass("text-danger");
              $("#editTargetsSaveButtonResponse").removeClass("text-primary");
              Console.log(data);
            }
            $("#editTargetsSaveButtonResponse").show();
          },
          'text'
        ).fail(function() {
          alert( "Could not update targets." );
        }).always(function(){
          $("#editTargetsSaveButton").html('Save Changes');
          setTimeout(function(){
            $("#editTargetsSaveButtonResponse").fadeOut();
          }, 1000);
        });

        e.preventDefault();
      });

?>
