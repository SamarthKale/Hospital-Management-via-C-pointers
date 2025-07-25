async function viewPatients() {
  const res = await fetch("/view");
  const data = await res.json();

  const tbody = document.querySelector("#patientTable tbody");
  tbody.innerHTML = "";
  data.forEach(p => {
    const row = `<tr>
      <td>${p.id}</td><td>${p.name}</td><td>${p.age}</td><td>${p.disease}</td><td>${p.memory}</td>
    </tr>`;
    tbody.innerHTML += row;
  });
}

async function searchPatient() {
  const id = document.getElementById("searchId").value;
  const res = await fetch(/search/${id});
  const data = await res.json();
  document.getElementById("searchResult").innerText =
    data.found ? Found: ${data.name}, ${data.age}, ${data.disease} : "Patient not found.";
}

async function deletePatient() {
  const id = document.getElementById("deleteId").value;
  await fetch(/delete/${id}, { method: "DELETE" });
  alert("Patient deleted (if found).");
  viewPatients();
}

document.getElementById("addForm").addEventListener("submit", async (e) => {
  e.preventDefault();
  const id = document.getElementById("id").value;
  const name = document.getElementById("name").value;
  const age = document.getElementById("age").value;
  const disease = document.getElementById("disease").value;

  await fetch("/add", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ id, name, age, disease }),
  });

  alert("Patient added!");
  viewPatients();
});
