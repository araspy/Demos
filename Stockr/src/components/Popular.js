import {React, useState, useEffect} from 'react'
import './Popup.css'

function Popular(props) {
    useEffect (()=>{
      loadData();
    },[])
    const [totals, setTotals]=useState({lemon:0, blue:0, punch:0});  //Total_Lemon, Total_Blue, Total_punch
    const loadData = async ()=>{

        // [{"StoreID":10,"StoreName":"Ted's BBQ","MachineID":10,"MachineStatus":"Active","NextMaintenance":"4/25/2022","Total_Lemon":21,"Total_Blue":15,"Total_Punch":18,"Rem_Lemon":7,"Rem_Blue":3,"Rem_Punch":2,"Flavor":"Lemonade","Size":1,"TimeDisp":"4/20/2022 5:18"}]
        const response =await fetch ("http://localhost:4000/popular");
        console.log("response", response);
        const data = await response.json();
        const totals ={lemon:data[0].Total_Lemon, blue:data[0].Total_Blue, punch:data[0].Total_Punch};
        console.log("totals", totals);
        setTotals(totals);
    }
    //trigger is boolean, if true, create popup, otherwise pass empty string
  return  (
    <div className="popup">
        <ol>
            <h1>Most Popular:</h1>
            <div>Lemon {totals.lemon}</div>
            <div>Blue {totals.blue}</div>
            <div>Punch {totals.punch}</div>
        </ol>
    </div>
  );
}

export default Popular