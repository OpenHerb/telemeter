"""
Bill of Materials
=================
Script to generate CSV of BOM from field values.
"""

import csv

board_revision = input("Board Revision: ")
fieldnames = ['Board Part No.', 'Manufacturer', 'Mfn Part No.', 'Unit Price']
row = {}

for field in fieldnames:
    row[field] = input("{}: ".format(field))
with open('bom-{}.csv'.format(board_revision), 'w+', newline='') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerow(row)