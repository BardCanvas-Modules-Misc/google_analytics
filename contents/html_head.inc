<?php
/**
 * Styles and scripts for the module
 *
 * @package    BardCanvas
 * @subpackage google_analytics
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *
 * @var config   $config
 * @var module   $this_module
 * @var template $template
 *
 * @var post_record  $post
 */

use hng2_base\config;
use hng2_base\module;
use hng2_base\template;
use hng2_modules\posts\post_record;

global $settings, $template, $post;

if( $template->layout == "admin" ) return;
if( $template->layout == "embeddable" ) return;

$code = $settings->get("modules:google_analytics.sitewide_code");

if( is_object($post) )
{
    $post_code = $post->get_meta("google_analytics");
    if( ! empty($post_code) ) $code = $post_code;
}

if( empty($code) ) return;
?>

<!-- [+] Google Analytics -->

<?= $code ?>


<!-- [-] Google Analytics -->

