<html><head><title>System Log</title>

<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Cache-Control" content="no-store, no-cache, must-revalidate, post-check=0, pre-check=0">
<meta http-equiv="Pragma" content="no-cache">

<link rel="stylesheet" href="/style/normal_ws.css" type="text/css">
<link rel="stylesheet" href="/style/controls.css" type="text/css">
<link rel="stylesheet" href="/style/windows.css" type="text/css">

<script type="text/javascript" src="/lang/b28n.js"></script>
<script type="text/javascript" src="/js/ajax.js"></script>
<script type="text/javascript" src="/js/controls.js"></script>
<script type="text/javascript" src="/js/validation.js"></script>

<script language="JavaScript" type="text/javascript">
Butterlate.setTextDomain("admin");

function uploadLogField(str)
{
	if (str == "-1")
	{
		document.getElementById("syslog").value =
		"Can not open LOG file\n"
	}
	else
	{	
		if (str == "-2")
		{
			document.getElementById("syslog").value =
			"Can not allocate memory\n"
		}
		else
		{
		document.getElementById("syslog").value = str;
		document.getElementById("syslog").scrollTop = document.getElementById("syslog").scrollHeight;
		}
	}
}

function updateLog()
{
	ajaxPerformRequest("/goform/syslog", uploadLogField);
}

function initTranslation()
{
	_TR("syslogTitle", "syslog title");

	_TR("syslogSysLog", "syslog system log");
	_TRV("syslogSysLogClear", "syslog clear");
	_TRV("syslogSysLogRefresh", "syslog refresh");
}

function pageInit()
{
	initTranslation();

	var form = document.LogdSetup;
	var klogd = '<% getCfgZero(1, "KLogd");%>';
	var syslogd = '<% getCfgZero(1, "SysLogd");%>';

	form.KLogd.value = (klogd == '1') ? '1' : '0';
	form.SysLogd.value = (syslogd == '1') ? '1' : '0';

	syslogdSelect(form);
	updateLog();
}

function clearlogclick()
{
	ajaxPostRequest("/goform/clearlog", 'stub=value', false, refreshlogclick);
}

function refreshlogclick()
{
	updateLog();
	return true;
}

function checkSetupForm(form)
{
	if (form.RemoteSysLogIP.value != '')
	{
		if (!validateIP(form.RemoteSysLogIP))
		{
			alert("Invalid Remote system log IP address");
			form.RemoteSysLogIP.focus();
		}
	}

	return true;
}

function syslogdSelect(form)
{
	displayElement([ 'rmtSysLogIP', 'klogdRow', 'syslog_view' ], form.SysLogd.value == '1');
}

</script>

</head>
<body onload="pageInit()">
<table class="body"><tr><td>
<h1 id="syslogTitle">System Log</h1>
<p>Here you can configure system logging</p>
<hr>

<!-- ================= System log setup ================= -->
<form method="post" name="LogdSetup" action="/goform/setuplog" onsubmit="checkSetupForm(this);">
<table class="form">
<tr>
	<td class="title"colspan="2" id="syslogSysLog">System Log Setup:</td>
</tr>
<tr>
	<td class="head">System logging deamon:</td>
	<td>
		<select name="SysLogd" onchange="syslogdSelect(this.form);">
			<option value="0">Disable</option>
			<option value="1">Enable</option>
		</select>
	</td>
</tr>
<tr id="klogdRow">
	<td class="head">Kernel logging daemon:</td>
	<td>
		<select name="KLogd">
			<option value="0">Disable</option>
			<option value="1">Enable</option>
		</select>
	</td>
</tr>
<tr id="rmtSysLogIP" style="display: none;">
	<td class="head">Remote system log IP:</td>
	<td>
		<input name="RemoteSysLogIP" value="<% getCfgGeneral(1, "RemoteSysLogIP"); %>">
	</td>
</tr>
</table>

<table class="buttons">
<tr>
	<td>
		<input type="submit" class="normal" value="Apply">
		<input type="hidden" name="submit-url" value="/adm/syslog.asp" >
	</td>
</tr>
</table>
</form>

<!-- ================= System log ================= -->
<table class="form" id="syslog_view" style="display: none;">
<tr>
	<td class="title"colspan="2" id="syslogSysLog">System Log: </td>
</tr>
<tr>
	<td colspan="2">
		<form method="post" name="SubmitClearLog1" action="/goform/clearlog">
			<input type="button" class="normal" value="Refresh" id="syslogSysLogRefresh" name="refreshlog" onclick="refreshlogclick();">&nbsp;
			<input type="button" class="normal" value="Clear" id="syslogSysLogClear" name="clearlog" onclick="clearlogclick();">
		</form>
	</td>
</tr>
<tr>
	<td>
		<textarea style="font-size: 8pt; width: 680px; height: 480px; border: 1px solid;" name="syslog" id="syslog" wrap="off" readonly="1">
		</textarea>
	</td>
</tr>
<tr>
	<td colspan="2">
		<form method="post" name="SubmitClearLog2" action="/goform/clearlog">
			<input type="button" class="normal" value="Refresh" id="syslogSysLogRefresh" name="refreshlog" onclick="refreshlogclick();">&nbsp;
			<input type="button" class="normal" value="Clear" id="syslogSysLogClear" name="clearlog" onclick="clearlogclick();">
		</form>
	</td>
</tr>
</table>

<div class="whitespace">&nbsp;</div>

</td></tr></table>
</body></html>
