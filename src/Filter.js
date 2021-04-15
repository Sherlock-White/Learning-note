import React, { Component } from 'react';

class Filter extends Component {
    render() {
        const handleStar = (car) =>{
            return this.props.handleStarCal(car.votes);
        }
        const handleClick = _ =>{
            //console.log('aaaaaaaa');
        }
        
        //get不到选中的值啊orz
        return(
            <tr>
                <th><select id = "selectBrand" onChange = {()=>{
                    let selectedValue = document.getElementById("selectBrand").value;
                    console.log(selectedValue);
                }}>
                    
                    <option value = 'all'>all</option>
                    {this.props.cars.map((car) => (
                        <option value = {car.brand} >{car.brand}</option>
                    ))}
                    </select></th>
                <th><select id = "selectStyle">
                    <option value = 'all'>all</option>
                    {this.props.cars.map((car) => (
                        <option value = {car.style} >{car.style}</option>
                    ))}
                    </select></th>
                <th><select id = "selectVotes">
                    <option value = 'all'>all</option>
                    {this.props.cars.map((car) => (
                        <option value = {car.votes} >{car.votes}</option>
                    ))}
                    </select></th>
                <th><select id = "selectStars">
                    <option value = 'all'>all</option>
                    {this.props.cars.map((car) => (
                        <option value = {handleStar(car)} >{handleStar(car)}</option>
                    ))}
                    </select></th>
                <th><button onClick = {handleClick}>Yes</button></th>
            </tr>
        );
    }
};

export default Filter;