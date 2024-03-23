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

global $config, $settings, $template, $post, $account;

if( $template->layout == "admin" ) return;
if( $template->layout == "embeddable" ) return;

$code = $settings->get("modules:google_analytics.sitewide_code");

if( is_object($post) )
{
    $post_code = $post->get_meta("google_analytics");
    if( ! empty($post_code) ) $code = $post_code;
}

if( empty($code) ) return;

if( $settings->get("modules:google_analytics.include_gdpr_box")
    && $template->layout != "popup"
    && ! $account->_exists
) {
    $vals = array(
        $_COOKIE["{$config->website_key}_gtag_gdpr_ast"] ,
        $_COOKIE["{$config->website_key}_gtag_gdpr_aud"] ,
        $_COOKIE["{$config->website_key}_gtag_gdpr_apz"] ,
        $_COOKIE["{$config->website_key}_gtag_gdpr_lyt"] ,
    );
    if( stristr($code, "gtag/js") && implode(",", $vals) == ",,," )
    {
        $vals = array("granted","granted","granted","granted");
        $template->set("@google_analytics.show_gdpr_box", true);
        $template->set("@google_analytics.switch_vals",   $vals);
        $code = "
            <script>
                window.dataLayer = window.dataLayer || [];
                function gtag(){dataLayer.push(arguments);}
                gtag('consent', 'default', {
                  'ad_storage':         '{$vals[0]}',
                  'ad_user_data':       '{$vals[1]}',
                  'ad_personalization': '{$vals[2]}',
                  'analytics_storage':  '{$vals[3]}',
                  'wait_for_update':    1000
                });
            </script>
            $code
        ";
    }
}
?>

<!-- [+] Google Analytics -->

<?= $code ?>


<!-- [-] Google Analytics -->

