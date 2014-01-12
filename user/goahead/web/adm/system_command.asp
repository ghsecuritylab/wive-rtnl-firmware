<html><head><title>System command</title>

<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Cache-Control" content="no-store, no-cache, must-revalidate, post-check=0, pre-check=0">
<meta http-equiv="Pragma" content="no-cache">

<link rel="stylesheet" href="/style/normal_ws.css" type="text/css">
<link rel="stylesheet" href="/style/controls.css" type="text/css">
<link rel="stylesheet" href="/style/windows.css" type="text/css">

<script type="text/javascript" src="/lang/b28n.js"></script>
<script type="text/javascript" src="/js/validation.js"></script>
<script type="text/javascript" src="/js/controls.js"></script>

<script language="JavaScript" type="text/javascript">
Butterlate.setTextDomain("admin");

function initTranslation()
{
	var e = document.getElementById("syscommandTitle");
	e.innerHTML = _("syscommand title");
	e = document.getElementById("syscommandIntroduction");
	e.innerHTML = _("syscommand introduction");

	e = document.getElementById("syscommandSysCommand");
	e.innerHTML = _("syscommand system command");
	e = document.getElementById("syscommandCommand");
	e.innerHTML = _("syscommand command");
	e = document.getElementById("syscommandApply");
	e.value = _("admin apply");
	e = document.getElementById("syscommandCancel");
	e.value = _("admin cancel");
}

function formCheck()
{
	if( document.SystemCommand.command.value == ""){
		alert("Please specify a command.");
		return false;
	}

	return true;
}

function setFocus()
{
	initTranslation();
	document.SystemCommand.command.focus();
}

</script>

</head>
<body onload="setFocus()">
<table class="body"><tr><td>
<h1 id="syscommandTitle">System Command</h1>
<p id="syscommandIntroduction"> Run system command as root: </p>
<hr>

<!-- ================= System command ================= -->
<form method="post" name="SystemCommand" action="/goform/SystemCommand">
<table class="form">
<tbody><tr>
  <td class="title" colspan="2" id="syscommandSysCommand">System command: </td>
</tr>
<tr>
  <td class="head" id="syscommandCommand">Command:</td>
	<td> <input type="text" name="command" size="50" maxlength="256" > </td>
</tr>
<tr><td colspan=2>
		<textarea style="font-size:8pt; width: 680px;" rows="20" wrap="off" readonly="1">
<% showSystemCommandASP(); %>
        </textarea></td>
</tr>
</table>
<input class="normal" value="Apply" id="syscommandApply" name="SystemCommandSubmit" onclick="return formCheck()" type="submit"> &nbsp;&nbsp;
<input class="normal" value="Reset" id="syscommandCancel" name="reset" type="reset">
</form> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

<!-- ================ repeat last system command ================= -->
<form method="post" name="repeatLastSystemCommand" action="/goform/repeatLastSystemCommand">
<input value="Repeat Last Command" id="repeatLastCommand" name="repeatLastCommand" type="submit"> &nbsp;&nbsp;
</form>

<div class="whitespace">&nbsp;</div>

</td></tr></table>
</body></html>
