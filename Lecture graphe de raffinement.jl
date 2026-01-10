
using JSON
json_data = open("raffinement.json", "r") do io
    JSON.parse(io)
end

println(json_data["abcdefghijk"])