<html>
<head>

<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Cache-Control" content="no-store, no-cache, must-revalidate, post-check=0, pre-check=0">
<meta http-equiv="Pragma" content="no-cache">

<link rel="stylesheet" href="/style/normal_ws.css" type="text/css">
<link rel="stylesheet" href="/style/controls.css" type="text/css">
<link rel="stylesheet" href="/style/windows.css" type="text/css">

<script type="text/javascript" src="/lang/b28n.js"></script>
<script type="text/javascript" src="/js/controls.js"></script>

<title>Station List</title>

<script language="JavaScript" type="text/javascript">
Butterlate.setTextDomain("wireless");

function initTranslation()
{
	_TR("stalistTitle", "stalist title");
	_TR("stalistIntroduction", "stalist introduction");
	_TR("stalistWirelessNet", "stalist wireless network");
	_TR("stalistMacAddr", "stalist macaddr");
}

function doDisconnectSta(form, mac)
{
	form.disconnectSta.value = mac;
	form.submit();
}

function PageInit()
{
	initTranslation();
}
</script>
</head>


<body onLoad="PageInit()">
<table class="body"><tr><td>

<h1 id="stalistTitle">Station List</h1>
<p id="stalistIntroduction"> Here you can monitor stations associated with this AP. </p>
<hr />

<form name="sta" action="/goform/disconnectSta" method="POST">

<table class="form">
  <tr> 
    <td class="title" colspan="12" id="stalistWirelessNet">Wireless Network</td>
  </tr>
  <tr>
    <th id="stalistMacAddr">MAC Address</th>
    <th>Con Time</th>
    <th>Aid</th>
    <th>PSM</th>
    <th>MIMO PS</th>
    <th>MCS</th>
    <th>BW</th>
    <th> SGI </th>
    <th>STBC</th>
    <th>MODE</th>
    <th>RSSI</th>
    <th>Actions</th>
  </tr>
  <% getWlanStaInfo(); %>
</table>

<table class="button">
<tr>
	<td>
		<input type="hidden" name="disconnectSta" value="*" />
		<input type="submit" value="Disconnect all" class="normal">
		<input type="hidden" name="submit-url" value="/wireless/stainfo.asp" >
	</td>
</tr>
</table>

</form>

</td></tr></table>
</body>
</html>

