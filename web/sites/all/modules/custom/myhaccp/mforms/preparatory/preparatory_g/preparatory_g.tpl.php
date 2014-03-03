<?php
/**
 * @file
 * Stage output template.
 */
?>
<section class="page">
  <h1>Process flow and confirmation</h1>
  <p class="intro">We have completed a flow diagram covering all steps in the manufacturing process of this product.</p>

  <?php if ($g_3): ?>
    <h3>A copy of our flow diagram can be obtained from the following location:</h3>
    <?php print $g_3; ?>
  <?php endif; ?>
