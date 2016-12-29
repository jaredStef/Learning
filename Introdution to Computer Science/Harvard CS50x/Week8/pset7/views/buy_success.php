<h3>Success!</h2>
<h4>You bought <?= htmlspecialchars($_SESSION["shares"]) ?> share(s) of <?= htmlspecialchars($_SESSION["ticker"]) ?> for $<?= htmlspecialchars($_SESSION["price"]) ?> dollars.</h4>
<h4>Your balance is now $<?= htmlspecialchars($_SESSION["bal"]) ?></h4>