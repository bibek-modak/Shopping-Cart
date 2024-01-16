const readlineSync = require('readline-sync');

let items = new Map();    // To store item name and quantity
let cost = new Map();     // To store item name and price of each item

let gift_wrap_fee = 0;
let shipping_fee = 0;
let greater_than_10 = false;
let greater_than_15 = false;

let capacity = parseInt(readlineSync.question('Enter the number of products you would like to add ->\n '));

if (capacity === 0) {
    console.log('Enter a valid number');
    process.exit(0);
}

let cnt = 0;

console.log('******************Welcome to the shopping cart***********************');
readlineSync.prompt();

for (let i = 1; i <= capacity; i++) {
    let quantity, item, price, gift;

    console.log(`Enter the name of product ${i}`);
    item = readlineSync.prompt();

    console.log(`Enter the cost of ${item}`);
    price = parseInt(readlineSync.prompt());

    cost.set(item, price);

    console.log(`Enter the quantity of ${item}`);
    quantity = parseInt(readlineSync.prompt());

    cnt += quantity;

    if (quantity > 10) greater_than_10 = true;
    if (quantity > 15) greater_than_15 = true;

    items.set(item, quantity);

    console.log('Would you like to add gift wrap as well? (yes/no)');
    gift = readlineSync.prompt();

    if (gift.toLowerCase() === 'yes') gift_wrap_fee += quantity;

    readlineSync.prompt();
}

shipping_fee = Math.ceil(cnt / 10) * 5;  // shipping fee which is 5$ per 10 items

let rule;
let total_quantity = 0;
let cart_total = 0;
let original_cart;

for (let [itemName, quantity] of items) {
    total_quantity += quantity;
    cart_total += cost.get(itemName) * quantity;
    cost.set(itemName, cost.get(itemName) * quantity);
}

original_cart = cart_total;

// Applying Discounts
if (total_quantity > 30 && greater_than_15) {
    for (let [itemName, quantity] of items) {
        if (quantity > 15) {
            let no = quantity - 15;
            let disc = (no * (cost.get(itemName) / quantity) * 5) / 100;
            cost.set(itemName, cost.get(itemName) - disc);
            cart_total -= disc;
        }
    }
    rule = 'tiered_50_discount';
} else if (total_quantity > 20 && total_quantity <= 30) {
    cart_total *= 0.9;
    rule = 'bulk_10_discount';
} else if (greater_than_10) {
    for (let [itemName, quantity] of items) {
        if (quantity > 10) {
            let disc = cost.get(itemName) * 0.05;
            cost.set(itemName, cost.get(itemName) - disc);
            cart_total -= disc;
        }
    }
    rule = 'bulk_5_discount';
} else if (cart_total > 200) {
    cart_total -= 10;
    rule = 'flat_10_discount';
} else {
    rule = 'Sorry not eligible for discounts';
}

console.log('*********************Bill****************************');

for (let [itemName, quantity] of items) {
    console.log(`product name: ${itemName} , Quantity: ${quantity} , Total Amount: ${cost.get(itemName)}$`);
}

console.log(`Subtotal is : ${original_cart}$`);
console.log(`Discount name: ${rule} , Discount amount:  ${original_cart - cart_total}$`);
console.log(`Shipping fee: ${shipping_fee}$ , Gift wrap fee: ${gift_wrap_fee}$`);

cart_total = cart_total - (gift_wrap_fee + shipping_fee);
console.log(`Total: ${cart_total}$`);
console.log('******************************************************');
console.log('Press enter to Exit :)');
readlineSync.prompt();
