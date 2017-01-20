<?php
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("sell_form.php");  
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        $ticker = $_POST["ticker"]; 
        $shareCount = $_POST["shareCount"]; 
        
        $row = CS50::query("SELECT * FROM `portfolios` WHERE userId={$_SESSION["id"]} AND symbol=\"{$ticker}\";")[0];
        $giveCash = 0; 
        $price = lookup($ticker)["price"]; 
        
        if (!preg_match("/^\d+$/", $shareCount))
        {
            apologize("Please enter a valid number"); 
        }
        // Check if user has that stock
        else if ($row == NULL)
        {
            apologize("You do not own any shares of \"{$ticker}\""); 
        }
        else if ($row["shares"] == $shareCount)
        {
            // DELETE ROW
            CS50::query("DELETE FROM `portfolios` WHERE userId={$_SESSION["id"]} AND symbol=\"{$ticker}\"");
            $giveCash = $row["shares"] * $price; 
        }
        else if ($row["shares"] < $shareCount)
        {
            // ERROR YOU DON't OWN THAT MANY SHARES 
            apologize("You only own {$row["shares"]} of \"{$ticker}\" and tried to sell {$shareCount}"); 
        }
        else if ($row["shares"] > $shareCount)
        {
            // UPDATE 
            $sellCount = $row["shares"] - $shareCount; 
            CS50::query("UPDATE `portfolios` SET shares={$sellCount} WHERE userId={$_SESSION["id"]} AND symbol=\"{$ticker}\";");
            $giveCash = $shareCount * $price; 
        }
        
        if ($price != 0)
        {
            $cash = CS50::query("SELECT * FROM `users` WHERE id={$_SESSION["id"]}")[0]["cash"];
            $cash += $giveCash; 
            CS50::query("UPDATE `users` SET cash={$cash} WHERE id={$_SESSION["id"]};"); 
            $_SESSION["shares"] = $shareCount;
            $_SESSION["ticker"] = $ticker;
            $_SESSION["price"] = $giveCash;
            $_SESSION["bal"] = $cash;
            CS50::query("INSERT INTO `history` (action, symbol, shares, price, date, userId) VALUES (\"SELL\", \"{$ticker}\", {$shareCount},
        {$giveCash}, CURRENT_TIMESTAMP, {$_SESSION["id"]});");
            render("sell_success.php", ["title" => "Sold!"]); 
        }
    }
    else 
    {
            apologize("Look to the sky! Is Jesus here? Because the world may be ending. We don't know how you did it, but you broke the page."); 
    }
?>