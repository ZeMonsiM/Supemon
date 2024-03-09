/*
 * shop.h
 *
 *  Created on: 27 févr. 2024
 *      Author: matth
 */

#ifndef SHOP_H_
#define SHOP_H_

void shopLoop(int *balance, inventory *playerInventory);
short getItemPrice(char itemname[16]);
void purchaseItem(char itemname[16], short amount, int *balance, inventory *playerInventory);
void sellItem(char itemname[16], short amount, int *balance, inventory *playerInventory);

#endif /* SHOP_H_ */
