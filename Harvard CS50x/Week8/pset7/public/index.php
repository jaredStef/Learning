<?php

    // configuration
    require("../includes/config.php"); 

    $positions = [];
    $rows = CS50::query("SELECT * FROM `portfolios` WHERE userId=?;", $_SESSION["id"]); 

    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]); 
        
        if ($stock !== false) 
        {
            $positions[] = [
                "name" => $stock["name"], 
                "price" => $stock["price"],
                "shares" => $row["shares"], 
                "symbol" => $row["symbol"]
            ];
        }
    }

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio"]);

?>
