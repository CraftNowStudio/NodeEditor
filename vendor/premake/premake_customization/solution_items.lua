-- Implement the solution_items command for solution-scope files
require('vstudio')

premake.api.register {
	name = "solution_items",
	scope = "workspace",
	kind = "list:string",
}

premake.override(premake.vstudio.sln2005, "projects", function(base, wks)
	if wks.solution_items and #wks.solution_items > 0 then
		local solution_folder_GUID = "{924C8D43-7E04-CF90-E70B-A8ECD3E26981}" -- See https://www.codeproject.com/Reference/720512/List-of-Visual-Studio-Project-Type-GUIDs
		premake.push("Project(\"" .. solution_folder_GUID .. "\") = \"Solution Items\", \"Solution Items\", \"{" .. os.uuid("Solution Items:" .. wks.name) .. "}\"")
		premake.push("ProjectSection(SolutionItems) = preProject")

		for _, path in ipairs(wks.solution_items) do
			premake.w(path .. " = " .. path)
		end

		premake.pop("EndProjectSection")
		premake.pop("EndProject")
	end
	base(wks)
end)