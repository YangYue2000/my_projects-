<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
<%
	String email = null;
    String message = null;
	HttpSession status = request.getSession(false);
	if (status != null) {
		if (status.getAttribute("email") != null) {
			email = (String)status.getAttribute("email");
			message = "in favorite page, email is: "+email;
		}
	} else {
		message = "ur not logged in yet, somethings wrong!";
	}
%>
<h1><%= message %></h1>
</body>
</html>