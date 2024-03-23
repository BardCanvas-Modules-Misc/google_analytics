<?php
/**
 * Pre-eof stuff
 *
 * @package    BardCanvas
 * @subpackage google_analytics
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *
 * @var config   $config
 * @var module   $this_module
 * @var template $template
 */

use hng2_base\config;
use hng2_base\module;
use hng2_base\template;

global $config, $template, $settings, $account;

if( ! $settings->get("modules:google_analytics.include_gdpr_box") ) return;
if( ! $template->get("@google_analytics.show_gdpr_box") ) return;
if( $account->_exists ) return;

$gdpr_message = $settings->get("modules:google_analytics.gdpr_box_legend");
if( empty($gdpr_message) ) $gdpr_message = $this_module->language->default_gdpr_message;
?>

<div id="google_analytics_gdpr_compliance_box" style="display: none; background: white; color: black; position: fixed; bottom: 20px; left: 50%; transform: translateX(-50%); max-width: 90vw; border-radius: 20px; padding: 20px; box-shadow: 5px 5px 20px black; font-family: arial, helvetica, sans-serif; font-size: 0.9em; line-height: normal;">
    
    <div class="intro">
        <?= $gdpr_message ?>
    </div>
    
    <div class="switches" style="display: none; margin-top: 20px">
        <div style="display: grid; gap: 20px; grid-template-columns: 1fr 1fr">
            <div>
                <span class='fa-pseudo-switch' data-value-on='granted' data-value-off='denied' onclick='toggle_fa_pseudo_switch(this); gdpr_update_switch(this);'>
                    <input type='hidden' name='ad_storage' value='granted'>
                    <span class='toggler toggle-on  fa fa-toggle-on'  style=''></span>
                    <span class='toggler toggle-off fa fa-toggle-off' style='display: none'></span>
                </span>
                <?= $this_module->language->ad_storage ?>
            </div>
            <div>
                <span class='fa-pseudo-switch' data-value-on='granted' data-value-off='denied' onclick='toggle_fa_pseudo_switch(this); gdpr_update_switch(this);'>
                    <input type='hidden' name='ad_user_data' value='granted'>
                    <span class='toggler toggle-on  fa fa-toggle-on'  style=''></span>
                    <span class='toggler toggle-off fa fa-toggle-off' style='display: none'></span>
                </span>
                <?= $this_module->language->ad_user_data ?>
            </div>
            <div>
                <span class='fa-pseudo-switch' data-value-on='granted' data-value-off='denied' onclick='toggle_fa_pseudo_switch(this); gdpr_update_switch(this);'>
                    <input type='hidden' name='ad_personalization' value='granted'>
                    <span class='toggler toggle-on  fa fa-toggle-on'  style=''></span>
                    <span class='toggler toggle-off fa fa-toggle-off' style='display: none'></span>
                </span>
                <?= $this_module->language->ad_personalization ?>
            </div>
            <div>
                <span class='fa-pseudo-switch' data-value-on='granted' data-value-off='denied' onclick='toggle_fa_pseudo_switch(this); gdpr_update_switch(this);'>
                    <input type='hidden' name='analytics_storage' value='granted'>
                    <span class='toggler toggle-on  fa fa-toggle-on'  style=''></span>
                    <span class='toggler toggle-off fa fa-toggle-off' style='display: none'></span>
                </span>
                <?= $this_module->language->analytics ?>
            </div>
        </div>
    </div>
    
    <div class="buttons_row aligncenter" style="margin-top: 20px">
        <span class="cust framed_content inlined pseudo_link state_active" onclick="gdpr_show_customize()">
            <?= $this_module->language->customize ?>
        </span>
        
        <span class="close framed_content inlined pseudo_link state_hover" style="display: none" onclick="gdpr_hide()">
            <?= $this_module->language->accept_selections ?>
        </span>
        
        <span class="rejall framed_content inlined pseudo_link state_highlight" onclick="gdpr_reject_all()">
            <?= $this_module->language->reject_all ?>
        </span>
        
        <span class="acall framed_content inlined pseudo_link state_ok" onclick="gdpr_accept_all()">
            <?= $this_module->language->accept_all ?>
        </span>
    </div>
    
</div>

<script>
    
    function gdpr_show()
    {
        $('#google_analytics_gdpr_compliance_box').show('slide', {direction: 'up'}, 'fast');
    }
    
    function gdpr_hide()
    {
        $('#google_analytics_gdpr_compliance_box').hide('slide', {direction: 'down'}, 'fast');
    }
    
    function gdpr_show_customize()
    {
        $('#google_analytics_gdpr_compliance_box .switches').show();
        $('#google_analytics_gdpr_compliance_box .buttons_row span:not(.close)').hide();
        $('#google_analytics_gdpr_compliance_box .buttons_row span.close').show();
    }
    
    function gdpr_update_switch(trigger)
    {
        var $trigger = $(trigger);
        var $input   = $trigger.find('input');
        var name     = $input.attr('name');
        var val      = $input.val();
        
        switch(name)
        {
            case 'ad_storage':         gdpr_update_consent_ad_storage(val);         break;
            case 'ad_user_data':       gdpr_update_consent_ad_user_data(val);       break;
            case 'ad_personalization': gdpr_update_consent_ad_personalization(val); break;
            case 'analytics_storage':  gdpr_update_consent_analytics_storage(val);  break;
        }
    }
    
    function gdpr_reject_all()
    {
        gdpr_update_consent_ad_storage('denied');
        gdpr_update_consent_ad_user_data('denied');
        gdpr_update_consent_ad_personalization('denied');
        gdpr_update_consent_analytics_storage('denied');
        gdpr_hide();
    }
    
    function gdpr_accept_all()
    {
        gdpr_update_consent_ad_storage('granted');
        gdpr_update_consent_ad_user_data('granted');
        gdpr_update_consent_ad_personalization('granted');
        gdpr_update_consent_analytics_storage('granted');
        gdpr_hide();
    }
    
    function gdpr_update_consent_ad_storage(val)         { gtag('consent', 'update', {'ad_storage':         val}); $.cookie('<?= $config->website_key ?>_gtag_gdpr_ast', val, {expires: 60, path: '/', domain: '<?= $config->cookies_domain ?>', secure: true}); }
    function gdpr_update_consent_ad_user_data(val)       { gtag('consent', 'update', {'ad_user_data':       val}); $.cookie('<?= $config->website_key ?>_gtag_gdpr_aud', val, {expires: 60, path: '/', domain: '<?= $config->cookies_domain ?>', secure: true}); }
    function gdpr_update_consent_ad_personalization(val) { gtag('consent', 'update', {'ad_personalization': val}); $.cookie('<?= $config->website_key ?>_gtag_gdpr_apz', val, {expires: 60, path: '/', domain: '<?= $config->cookies_domain ?>', secure: true}); }
    function gdpr_update_consent_analytics_storage(val)  { gtag('consent', 'update', {'analytics_storage':  val}); $.cookie('<?= $config->website_key ?>_gtag_gdpr_lyt', val, {expires: 60, path: '/', domain: '<?= $config->cookies_domain ?>', secure: true}); }
    
    setTimeout(function() { $(document).ready(function() { gdpr_show(); }); }, 1000);
    
</script>
