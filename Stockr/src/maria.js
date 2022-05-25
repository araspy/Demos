var MySql = require('sync-mysql');


let MySQLConnObj = {
    host: 'database-1.cca3svhf41bs.us-east-2.rds.amazonaws.com',
    user: 'admin',
    password: 'coolbeans1',
    database: 'Stockr_Overall'
};


var conn = new MySql(MySQLConnObj);


const rows = conn.query("SELECT * FROM users");


console.log(rows);