# Backend integration

The public library only defines the small `IESP32AIBackend` contract. A project can implement that contract around its generated inference SDK.

Do not commit proprietary model files into this library. Keep trained models in the application repository or release package where their license and training provenance are documented.
