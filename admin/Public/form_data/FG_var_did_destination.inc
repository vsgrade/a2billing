<?php

/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**
 * This file is part of A2Billing (http://www.a2billing.net/)
 *
 * A2Billing, Commercial Open Source Telecom Billing platform,   
 * powered by Star2billing S.L. <http://www.star2billing.com/>
 * 
 * @copyright   Copyright (C) 2004-2009 - Star2billing S.L. 
 * @author      Belaid Arezqui <areski@gmail.com>
 * @license     http://www.fsf.org/licensing/licenses/agpl-3.0.html
 * @package     A2Billing
 *
 * Software License Agreement (GNU Affero General Public License)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
**/



getpost_ifset(array('id', 'destination', 'id_cc_card', 'id_cc_did', 'activated', 'priority', 'id_trunk', 'voip_call'));

if ( (empty($form_action) || $form_action=="list")) {
	$HD_Form = new FormHandler("cc_did_destination LEFT JOIN cc_did ON cc_did.id = cc_did_destination.id_cc_did","Did Destination");
} else {
	$HD_Form = new FormHandler("cc_did_destination");
}

$HD_Form -> FG_DEBUG = 0;
$HD_Form -> FG_TABLE_DEFAULT_ORDER = "did DESC, priority";
$HD_Form -> FG_TABLE_DEFAULT_SENS = "ASC";
$HD_Form -> FG_LIMITE_DISPLAY = 20;

$HD_Form -> FG_TABLE_ID = 'cc_did_destination.id';

$HD_Form ->FG_LIST_ADDING_BUTTON1 = true;
$HD_Form ->FG_LIST_ADDING_BUTTON_LINK1 = "A2B_entity_did_destination.php?form_action=ask-add&section=".$_SESSION["menu_section"];
$HD_Form ->FG_LIST_ADDING_BUTTON_ALT1 = $HD_Form ->FG_LIST_ADDING_BUTTON_MSG1 = gettext("Add DESTINATION");
$HD_Form ->FG_LIST_ADDING_BUTTON_IMG1 = Images_Path ."/world_add.png" ;


$actived_list = Constants::getActivationList();


$billingtype_list = Constants::getBillingTypeList();
// -- billtype: 0 = fix per month + dialoutrate, 1= fix per month, 2 = dialoutrate, 3 = free

$priority_list = array();
for ($k=1;$k<=5;$k++)
    $priority_list["$k"]  = array( "$k", "$k");

$validated_list = array();
$validated_list["1"] = array( gettext("Validated"), "1");
$validated_list["0"] = array( gettext("Pending"), "0");


$HD_Form -> AddViewElement(gettext("DID"), "did", "12%", "center", "sort", "15");
$HD_Form -> AddViewElement(gettext("ACTIVE"), "activated", "5%", "center", "sort", "", "list", $actived_list);
$HD_Form -> AddViewElement(gettext("PRIOR"), "priority", "5%", "center", "sort", "", "list", $priority_list);
$HD_Form -> AddViewElement(gettext("DESTINATION"), "destination", "15%", "center", "sort");
$HD_Form -> AddViewElement(gettext("VOIP"), "voip_call", "5%", "center", "sort", "", "list", $actived_list);
$HD_Form -> AddViewElement(gettext("CREATION DATE"), "creationdate", "15%", "center", "sort", "16", "", "", "", "", "", "display_dateformat");
$HD_Form -> AddViewElement(gettext("ACCOUNT NUMBER"), "id_cc_card", "15%", "center", "sort", "", "lie_link", "cc_card", "username,id", "id='%id'", "%1", "", "A2B_entity_card.php");
$HD_Form -> AddViewElement(gettext("MINUTES USED"), "secondusedreal", "10%", "center", "SORT", "30", "", "", "", "", "", "display_minute");
$HD_Form -> AddViewElement(gettext("VALIDATED"), "validated", "10%", "center", "sort", "", "list", $validated_list);


// added a parameter to append  FG_TABLE_ID  ( by default ) or disable 0.
$HD_Form -> FieldViewElement ('cc_did.did, cc_did_destination.activated, priority, destination, voip_call, cc_did_destination.creationdate, id_cc_card, cc_did_destination.secondusedreal, validated');

$HD_Form -> FG_ACTION_SIZE_COLUMN = '15%';

$HD_Form -> CV_NO_FIELDS  = gettext("NO DID DESTINATIONS HAVE BEEN CREATED!");
$HD_Form -> CV_DISPLAY_LINE_TITLE_ABOVE_TABLE = false;
$HD_Form -> CV_TEXT_TITLE_ABOVE_TABLE = '';
$HD_Form -> CV_DISPLAY_FILTER_ABOVE_TABLE = false;


$HD_Form -> FG_EDITION = true;
$HD_Form -> FG_DELETION = true;
$HD_Form -> FG_ADDITION = true;


// TODO integrate in Framework
if ($form_action=="ask-add"){
	$begin_date = date("Y");
	$begin_date_plus = date("Y")+20;
	$end_date = date("-m-d H:i:s");
	$comp_date = "value='".$begin_date.$end_date."'";
	$comp_date_plus = "value='".$begin_date_plus.$end_date."'";
}



$HD_Form -> AddEditElement (gettext("ACTIVATED"),
	"activated",
	'1',
	"RADIOBUTTON",
	"",
	"",
	gettext("Choose if you want to activate this card"),
	"" , "", "", gettext("Yes").":1, - ".gettext("No").":0",   "", "" , "", "");

$HD_Form -> AddEditElement (gettext("DESTINATION"),
	"destination",
	'$value',
	"INPUT",
	"size=50 maxlength=120",
	"0",
	gettext("Insert the DID"),
	"", "", "", "", "", "", "", gettext("Enter the phone number you wish to call, or the VoIP client to reach, or QUEUE to go. (ie: 347894999 or SIP/jeremy@182.212.1.45 or QUEUE myqueue,hknRt,,,300). If the call is VoIP or QUEUE, the 'VoIP_Call' must be set to yes."));

$HD_Form -> AddEditElement (gettext("TIMEOUT"),
	"timeout",
	'$value',
	"INPUT",
	"size=50 maxlength=3",
	"22",
	gettext("Insert max 3 digits"),
	"", "", "", "", "", "", "", gettext("Maximum time, in seconds, that the Dial command is to wait for a channel to answer"));

$HD_Form -> AddEditElement (gettext("VOIP_CALL"),
	"voip_call",
	'0',
	"RADIOBUTTON",
	"",
	"",
	gettext("Choose if you want to not use the trunk and let the asterisk go to QUEUE or call directly the destination (ie, Destination : SIP/jeremy@182.212.1.45)"),
	"", "",  "", gettext("Yes").":1, - ".gettext("No").":0", "", "", "", gettext("If the call is VoIP or QUEUE, that must be set to 'Yes'"));

if ($form_action!='ask-edit' && $form_action!='edit') {
	
	$HD_Form -> AddEditElement (gettext("CUSTOMER ID"),
		"id_cc_card",
		'',
		"POPUPVALUE",
		"size=30 maxlength=50",
		"4",
		gettext("Insert the Id Customer ID"),
		"" , "", "", "", "",
		"A2B_entity_card.php?popup_select=1&"
		, ", 'CardNumberSelection','width=550,height=550,top=100,left=100,scrollbars=1'" ,
		gettext("Set the Customer ID."));


	$HD_Form -> AddEditElement (gettext("DID"),
		"id_cc_did",
		'$value',
		"SELECT",
		"", "", "",
		"sql",
		"cc_did",
		"did, id",
		"", "", "%1", "" , "");
}

$HD_Form -> AddEditElement (gettext("VALIDATED"),
	"validated",
	"",
	"SELECT",
	"",
	"",
	"",
	"list" , "", "",  "", $validated_list, "%1" , "" , "");

$HD_Form -> AddEditElement (gettext("PRIORITY"),
	"priority",
	"",
	"SELECT",
	"",
	"",
	"",
	"list" , "", "",  "", $priority_list, "%1" , "" , "");

$HD_Form -> AddEditElement (gettext("ANSWER"),
	"answer",
	'0',
	"RADIOBUTTON",
	"",
	"",
	gettext("Choose 'Yes' if you want to answer on the call"),
	"" , "", "", gettext("Yes").":1, - ".gettext("No").":0", "", "", "", gettext("Choose if you want to answer on the call before playing PLAY_SOUND"));

$HD_Form -> AddEditElement (gettext("PLAY_SOUND"),
	"playsound",
	'$value',
	"INPUT",
	"size=50 maxlength=50",
	"",
	gettext("Insert the path and name of sound file"),
	"" , "", "", "", "", "", "", gettext("Play sound before calling DESTINATION. ie 'ivr/wait-please'"));


if ($form_action!='ask-edit' && $form_action!='edit') {
	$HD_Form -> FieldEditElement ('activated, destination, timeout, voip_call, id_cc_card, id_cc_did, validated, priority, answer, playsound');
} else {
	$HD_Form -> FieldEditElement ('activated, destination, timeout, voip_call, validated, priority, answer, playsound');
}

// Set the filter variables
$HD_Form -> FG_FILTER_APPLY = true;
$HD_Form -> FG_FILTERFIELD = 'did';
$HD_Form -> FG_FILTERFIELDNAME = 'did';

if (isset($filterprefix)  &&  (strlen($filterprefix)>0)) {
	if (strlen($HD_Form -> FG_TABLE_CLAUSE)>0) $HD_Form -> FG_TABLE_CLAUSE.=" AND ";
	$HD_Form -> FG_TABLE_CLAUSE .= "cc_did.did like '$filterprefix%'";
}


$HD_Form -> FG_INTRO_TEXT_EDITION= gettext("You can modify, through the following form, the different properties of your ".$HD_Form->FG_INSTANCE_NAME);
$HD_Form -> FG_INTRO_TEXT_ASK_DELETION = gettext("If you really want remove this")." ".$HD_Form->FG_INSTANCE_NAME.", ".gettext("click on the delete button.");
$HD_Form -> FG_INTRO_TEXT_ADD = gettext("you can add easily a new")." ".$HD_Form->FG_INSTANCE_NAME."<br>".gettext("Fill the following fields and confirm by clicking on the button add.");


$HD_Form -> FG_INTRO_TEXT_ADITION = '';
$HD_Form -> FG_TEXT_ADITION_CONFIRMATION = gettext("Your new")." ".$HD_Form->FG_INSTANCE_NAME." ".gettext("has been inserted. <br>");


$HD_Form -> FG_BUTTON_EDITION_SRC = $HD_Form -> FG_BUTTON_ADITION_SRC  = Images_Path . "/cormfirmboton.gif";
$HD_Form -> FG_BUTTON_EDITION_BOTTOM_TEXT = $HD_Form -> FG_BUTTON_ADITION_BOTTOM_TEXT = gettext("Click 'Confirm Data' to continue");

$HD_Form -> FG_ADDITIONAL_FUNCTION_AFTER_ADD = 'did_destination_add';
$HD_Form -> FG_ADDITIONAL_FUNCTION_AFTER_DELETE = 'did_destination_del';

$HD_Form -> FG_GO_LINK_AFTER_ACTION_ADD = $_SERVER['PHP_SELF']."?id=";
$HD_Form -> FG_GO_LINK_AFTER_ACTION_EDIT = $_SERVER['PHP_SELF']."?id=";
$HD_Form -> FG_GO_LINK_AFTER_ACTION_DELETE = $_SERVER['PHP_SELF']."?id=";



