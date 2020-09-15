<%@ page language="java" session="false" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Home Page</title>

<link rel="stylesheet" type="text/css" href="style.css">
<style>
#body {
	/* background-image: url("main.jpg"); */
	width: 990px;
	height: 330px;
	margin-top: 60px;
	margin-left: auto;
	margin-right: auto;
}

#image {
	width: 990px;
	height: 330px;
}

</style>
</head>
<body>
<!-- determining the login status -->
<%
	String display = null;
	String log = null;
	String link = null;
	HttpSession status = request.getSession(false);
	if (status != null) {
		if (status.getAttribute("email") != null) {
			System.out.println("in Home page, email is: "+status.getAttribute("email"));
			log = "Log Out";
			link = "LogOutServlet";
		} else {
			log = "Login / Sign Up";
			display = "display: none;";
			link = "login.html";
		}
	} else {
		log = "Login / Sign Up";
		display = "display: none;";
		link = "login.html";
	}
%>
	<div id="header">
		<img id="logo" src="logo.png">
		<div id="nav">
			<a href="home.jsp">Home</a> 
			<a href="favorite.jsp"
				style="<%=display%>">Favorites</a> 
			<a href="<%=link%>"><%=log%></a>
		</div>
	</div>
	<div id="body"><img id="image" src="main.jpg"></div>
	<%@include file="searchbar.html" %>
</body>
</html>