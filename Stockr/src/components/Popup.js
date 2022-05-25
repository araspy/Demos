import React from 'react'
import './Popup.css'

function Popup(props) {
    //trigger is boolean, if true, create popup, otherwise pass empty string
  return (props.trigger) ? (
    <div className="popup">
        <div className="popup-inner">
            <button className="close-btn" onClick={() => props.setTrigger(false)}>
              close
              </button>
            { props.children }
        </div>
        Popup
    </div>
  ) : "";
}

export default Popup