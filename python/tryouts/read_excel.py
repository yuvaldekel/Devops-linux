import xlrd
import xlsxwriter

xlrd.xlsx.ensure_elementtree_imported(False, None)
xlrd.xlsx.Element_has_iter = True

work_book = xlrd.open_workbook(r".\first.xlsx")
work_sheet = work_book.sheet_by_index(0)

row = work_sheet.row(1)
row_values = [cell.value for cell in row]

new_work_book = xlsxwriter.Workbook(r".\first.xlsx")
new_work_sheet = new_work_book.add_worksheet()

new_work_sheet.write_row(1, 0, row_values)

new_work_book.close()