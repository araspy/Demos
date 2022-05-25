import {React, useState, useEffect} from 'react'
import './Popup.css'

function Overall(props) {
    useEffect (()=>{
      loadData();
    },[])
    const [list, setList]=useState([]);
    const loadData = async ()=>{
        const response =await fetch ("http://localhost:4000/overall");
        console.log("response", response);
        const data = await response.json();
        console.log("data", data);
        setList(data);
    }
    //trigger is boolean, if true, create popup, otherwise pass empty string
  return  (
    <div className="popup">
        <ol>
        {list.length==0?<div>loading...</div>:list.map((row) => (
          <li>{row.Flavor}</li>

        ))}
        </ol>
    </div>
  );
}

export default Overall