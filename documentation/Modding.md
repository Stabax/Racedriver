About modding
=============

## Menu elements

<table>
  <tr>
    <th>Tag</th>
    <th>Attribute</th>
    <th>Description</th>
  </tr>
  <!-- Text -->
  <tr>
    <td rowspan="2">Text</td>
    <td colspan="2">Non selectable entry of characters</td>
  </tr>
  <tr>
    <td>Id</td>
    <td>Sets id of text unit to grab from locale file</td>
  </tr>
  <!-- Sep -->
  <tr>
    <td>Sep</td>
    <td colspan="2">Non selectable horizontal separator</td>
  </tr>
  <!-- Button -->
  <tr>
    <td rowspan="4">Button</td>
    <td colspan="2">Clickable entry</td>
  </tr>
  <tr>
    <td>Type</td>
    <td>{Intern, Goto, Script}</td>
  </tr>
  <tr>
    <td>Target</td>
    <td>Source, function or scriptId to execute</td>
  </tr>
  <tr>
    <td>Path</td>
    <td>Path where the source is located if extern</td>
  </tr>
  <!-- Input -->
  <tr>
    <td rowspan="2">Input</td>
    <td colspan="2">Field to input characters</td>
  </tr>
  <tr>
    <td>Id</td>
    <td>Sets control id for interaction in script</td>
  </tr>
  <!-- Select -->
  <tr>
    <td rowspan="2">Select</td>
    <td colspan="2">multi-value selection item</td>
  </tr>
  <tr>
    <td>Id</td>
    <td>Sets control id for interaction in script</td>
  </tr>
  <!-- Option -->
  <tr>
    <td rowspan="2">Option</td>
    <td colspan="2">selectable item from select</td>
  </tr>
  <tr>
    <td>Value</td>
    <td>Sets value corresponding to text</td>
  </tr>
  <!-- Script -->
  <tr>
    <td rowspan="2">Script</td>
    <td colspan="2">Lua embedded script called by Id, or position in menu</td>
  </tr>
  <tr>
    <td>Id</td>
    <td>Sets control id for interaction in script</td>
  </tr>
</table>