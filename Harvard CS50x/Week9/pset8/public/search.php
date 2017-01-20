<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
// could be a city, state, or postal code 
    $i = 0; 
    
    $items = CS50::query("SELECT * FROM `places` WHERE MATCH(`postal_code`, `place_name`, `admin_name1`, `admin_code1`) AGAINST (\"{$_GET["geo"]}\");");
    foreach ($items as $item)
    {
        // Adds if the same isn't already in it
        // Weird code because if I don't do it like this it throws warnings
        // which mess up the JSON 
        if ($i == 0)
        {
            $places[$i] = $item; 
            $i += 1; 
        }
        else if ($places[$i - 1]["place_name"] != $item["place_name"] || $places[$i - 1]["admin_code1"] != $item["admin_code1"]) 
        {
            $places[$i] = $item; 
            $i += 1;  
        }
        
        
    }
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>