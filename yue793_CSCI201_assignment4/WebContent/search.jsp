<%@page import="org.json.simple.JSONArray"%>
<%@page import="java.io.InputStreamReader"%>
<%@page import="org.json.simple.JSONObject"%>
<%@page import="org.json.simple.parser.JSONParser"%>
<%@page import="java.net.HttpURLConnection"%>
<%@page import="java.net.URL"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Search</title>
<style>
#body{
width:990px;
margin-left:auto;
margin-right:auto;
}
h2{
float:left;
opacity:0.7;
}
#result{
width:990px;
height:273px;
padding:40px;
}
#img{
width:270px;
height:270px;
float:left;
margin-right:30px;
}
#content{
opacity: 0.7;
width:600px;
float:left;
height:270px;
padding:15px;
font-size:25px;
line-height:28px;
}
#pic{
height: 270px;
width: 270px;
border-radius: 20%;
}
</style>
</head>
<body>
	<%
		String display = null;
		String log = null;
		String link = null;
		HttpSession status = request.getSession(false);
		if (status != null) {
			if (status.getAttribute("email") != null) {
				System.out.println("in Search page, email is: " + status.getAttribute("email"));
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
		String sort = request.getParameter("sort");
		String lon = request.getParameter("lon");
		String lat = request.getParameter("lat");
		String restaurant = request.getParameter("restaurant");
		restaurant = restaurant.trim().replaceAll(" ", "_").replaceAll("’", "'");
		String prefix = "https://api.yelp.com/v3/businesses/search?";
		String query = "term="+restaurant+"&latitude="+lat+"&longitude="+lon+"&sort_by="+sort;
		System.out.println("the query is: "+prefix+query);
		URL url = new URL(prefix+query);
		HttpURLConnection con = (HttpURLConnection)url.openConnection();
		con.setRequestMethod("GET");
		con.setRequestProperty("Authorization", "Bearer ysErQw8YVSX9lVbf1AOR7VETA6RuXoVL12CcC-HYJch4G6XgiuJk4zrKlDV881AnEPvtWB1Ma8ChR-ZtQYXtROhiRQhP22OUMWmuGUe7Ja7WVwvTn8YK2YHUIQ1_XnYx");
		JSONParser parser = new JSONParser();
		JSONObject obj = (JSONObject)parser.parse(new InputStreamReader(con.getInputStream()));
		JSONArray array = (JSONArray)obj.get("businesses");
		String total = obj.get("total").toString();
		System.out.println("total result: "+total);
/* 		System.out.println(r1);
		System.out.println(price1);
		System.out.println(phone1);
		System.out.println(type1);
		System.out.println(url1);
		System.out.println(name1);
		System.out.println(image);
		System.out.println(address); */
	%>
	<div id="header">
		<img id="logo" src="logo.png">
		<div id="nav">
			<a href="home.jsp">Home</a> <a href="favorite.jsp"
				style="<%=display%>">Favorites</a> <a href="<%=link%>"><%=log%></a>
		</div>
	</div>
	<div id="body">
	<%@include file="searchbar.html" %>
	<br>
		<h2 >Results for "<%=restaurant%>"</h2><br><br><br><br><br>
		<hr>
		<%
		int bound = 10;
		if(array.size()<10){
			bound = array.size();
		}
		for(int i=0;i<bound;i++){
			String r = ((JSONObject)array.get(i)).get("rating").toString();
			String price = ((JSONObject)array.get(i)).get("price").toString();
			String phone = ((JSONObject)array.get(i)).get("phone").toString();
			String type = ((JSONObject)((JSONArray)((JSONObject)array.get(i)).get("categories")).get(0)).get("title").toString();
			String r_url = ((JSONObject)array.get(i)).get("url").toString();
			int target = r_url.indexOf('?');
			if(target != -1){
				r_url = r_url.substring(0, target);
			}
			String name = ((JSONObject)array.get(i)).get("name").toString();
			String id = ((JSONObject)array.get(i)).get("id").toString();
			String image = ((JSONObject)array.get(i)).get("image_url").toString();
			String a1 = ((JSONObject)((JSONObject)array.get(i)).get("location")).get("address1").toString();
			String city = ((JSONObject)((JSONObject)array.get(i)).get("location")).get("city").toString();
			String state = ((JSONObject)((JSONObject)array.get(i)).get("location")).get("state").toString();
			String zip = ((JSONObject)((JSONObject)array.get(i)).get("location")).get("zip_code").toString();
			String address = a1+", "+city+", "+state+" "+zip;
		%>
		<div id="result">
			<div id="img">
				<a href="details.jsp?address=<%=address%>&image=<%=image%>&type=<%=type%>&rating=<%=r%>&url=<%=r_url%>&name=<%=name%>&id=<%=id%>&price=<%=price%>&phone=<%=phone%>"><img id="pic" src="<%=image%>"></a>
			</div>
			<div id="content">
				<strong><%=name%></strong><br>
				<p><%=address%></p>
				<p><a href="<%=r_url%>" style="color:black;text-decoration:none"><%=r_url%></a><br></p>
			</div>
		</div>
		<br>
		<%
		}
		%>
	</div>

</body>
</html>