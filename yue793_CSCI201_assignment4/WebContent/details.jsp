<%@page import="java.sql.SQLException"%>
<%@page import="com.mysql.cj.jdbc.Driver"%>
<%@page import="java.sql.DriverManager"%>
<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.Statement"%>
<%@page import="java.sql.Connection"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>details</title>
<link rel="stylesheet" type="text/css" href="style.css">
<script type="text/javascript">
	function favorite(){
		var text = document.getElementById("b");
		var xhttp = new XMLHttpRequest();
		if(text.innerHTML === "add to favorites"){
			xhttp.open("GET","AddFavorite?name="+document.getElementById("name").value+"&&id="+document.getElementById("id").value+"&&r="+document.getElementById("R").value+"&&image="+document.getElementById("image").value+"&&address="+document.getElementById("address").value+"&&url="+document.getElementById("url").value,true);
			xhttp.send();
			xhttp.onreadystatechange = function(){
				text.innerHTML = "remove from favorites";
			}
		}
		else{
			xhttp.open("GET","RemoveFavorite?id="+document.getElementById("id").value+"&&address="+document.getElementById("address").value,true);
			xhttp.send();
			xhttp.onreadystatechange = function(){
				text.innerHTML = "add to favorites";
			}  
		}
	}
</script>
</head>
<body>
	<%
		String display = null;
		String log = null;
		String link = null;
		HttpSession status = request.getSession(false);
		String email = "";
		boolean existed = true;
		boolean logged_in = true;
		String button_text = "add to favorites";
		if (status != null) {
			if (status.getAttribute("email") != null) {
				email = status.getAttribute("email").toString();
				System.out.println("in Search page, email is: " + status.getAttribute("email"));
				log = "Log Out";
				link = "LogOutServlet";
			} else {
				log = "Login / Sign Up";
				display = "display: none;";
				link = "login.html";
				logged_in = false;
			}
		} else {
			log = "Login / Sign Up";
			display = "display: none;";
			link = "login.html";
		}
		String price = request.getParameter("price");
		String address = request.getParameter("address");
		String rating = request.getParameter("rating");
		String name = request.getParameter("name");
		String type = request.getParameter("type");
		String phone = request.getParameter("phone");
		String image = request.getParameter("image");
		String url = request.getParameter("url");
		String uID ="";
		if(logged_in){
			String buffer_uID = "SELECT s.userID from saluser s where s.email="+"'"+email+"'";
			Connection conn = null;
			Statement st = null;
			ResultSet rs = null;
			try {
				DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
				conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/hw4?serverTimezone=UTC&user=root&password=Dan15110278550.");
				st = conn.createStatement();
				rs=st.executeQuery(buffer_uID);
				if(rs.next()){
					uID = rs.getString("userID");
				}
				System.out.println("the user ID is "+uID);
				
				String buffer_rID = "SELECT * from favorites f where f.address ="+"'"+address+"'"+"and f.userID ="+"'"+uID+"'";
				rs=st.executeQuery(buffer_rID);
				if(rs.isBeforeFirst()){
					/* check if something exists */
					button_text = "remove from favorites";
				}
			} catch ( SQLException e) {
				e.printStackTrace();
			}finally {
				try {
					if (st != null) {
						st.close(); 
					}
					if (conn != null){
						conn.close(); 
					}
				}
				catch (SQLException sqle){ 
					System.out.println(sqle.getMessage());
				} 
			}
		}
		
	%>
	<div id="header">
		<img id="logo" src="logo.png">
		<div id="nav">
			<a href="home.jsp">Home</a> <a href="favorite.jsp"
				style="<%=display%>">Favorites</a> <a href="<%=link%>"><%=log%></a>
		</div>
	</div>
		<%@include file="searchbar.html" %>
	<p><%=price %></p>
	<input type="hidden" id = "address" value="<%=address%>">
	<p><%=address %></p>
	<input type="hidden" id = "R" value="<%=rating%>">
	<p><%=rating %></p>
	<p><%=type %></p>
	<input type="hidden" id = "name" value="<%=name%>">
	<p><%=name %></p>
	<p><%=phone %></p>
	<input type="hidden" id = "image" value="<%=image%>">
	<p><%=image %></p>
	<input type="hidden" id = "url" value="<%=url%>">
	<p><%=url %></p>
	<input type="hidden" id = "id" value="<%=uID%>">
	<button id="b" style="<%=display%>" onclick="favorite()"><%= button_text %></button>
</body>
</html>