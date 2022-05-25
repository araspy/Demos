console.log("starting server...");
//var http = require("http");
var MySql = require('sync-mysql');

var cors = require('cors');
var express = require("express");

//const mongoose = require ('mongoose');
//const mongoose = require ('mongoose');
const bodyParser = require('body-parser');

//const db = require('./postgres');

const fs = require('fs');
const PORT = 4000;
console.log("libraries loaded");
//app.use('express.json');
/*
curl -d '{"name":"My Value"}' -H "Content-Type: application/json" http://127.0.0.1:4000/jsonTest
{"MyKey":"My Value"}
*/
var app = express();
app.use(bodyParser.urlencoded({ extended: false }));
//app.use(upload());

app.use(cors())

//app.use(upload);
var GV_RES = null;
const conn = getConn();

app.get("/users", async(req, res) => {
   // const conn = getConn();
    const users = conn.query ("SELECT * FROM users");
 //   conn.close();
  //  conn=null;
    res.send(users);
});
//SELECT * FROM Stockr_Overall.Overall;
app.get("/overall", async(req, res) => {
  //  const conn = getConn();
    const data = conn.query ("SELECT * FROM Stockr_Overall.Overall");
  //  conn.close();
  //  conn=null;
    res.send(data);
});
app.get("/popular", async(req, res) => {
 //   const conn = getConn();
    const data = conn.query ("SELECT * FROM Stockr_Overall.Overall ORDER BY TimeDisp DESC LIMIT 1");
   // conn.close();
   // conn=null;
    res.send(data);
});

// restaurants
// restaurats?state=IN
// users[0].username  JSON? array of strucs.
app.get("/restaurants", async(req, res) => {
    const conn = getConn();
    var query = "SELECT * FROM restaurants";
    const st = req.query.state;
    if(st)
    {
        query += ` WHERE state = '${st}'`;
        // sprintf (Query, "WHERE state = '%s'", st)
    }
    const restaurants = conn.query ();
    res.send(restaurants);
});

app.get("/", (req, res) => {
    res.send("hello");
});

app.get("/uploadForm", (req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.write('<form action="fileupload" method="post" target="sub" enctype="multipart/form-data">');
    res.write('<input type="text" name="id" value="0"><br>');
    res.write('<input type="file" name="filetoupload"><br>');
    res.write('<input type="submit">');
    res.write('</form><iframe id="sub" name="sub"/>');
    res.end();
});


console.log("about to lisen");
app.listen(PORT, () => {
    console.log(`Running on port: ${PORT}`);
});

function getFileContents(fileName) {
    console.log("get file: " + fileName);
    var fs = require('fs');
    return fs.readFileSync(fileName, 'utf8');
}

function getConn(){
    const content = getFileContents("myconn.json");
    console.log("content", content)

    const connObj = JSON.parse(content);
    var conn = new MySql(connObj);
    return conn;
}