def can_build(env, platform):
    return not platform == "android" and not platform == "mono"


def configure(env):
    pass


def get_doc_classes():
    return [
        "JavaScript",
        "JavaScriptModule",
    ]


def get_doc_path():
    return "doc_classes"
